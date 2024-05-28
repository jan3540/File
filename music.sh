#!/bin/bash

# 使用.my.conf文件安全登录数据库
MYSQL_CREDENTIALS="/home/.my.conf"

# 检查.my.conf文件是否存在
if [ ! -f "$MYSQL_CREDENTIALS" ]; then
    dialog --title "错误" --msgbox "数据库凭证文件不存在。" 5 40
    exit 1
fi

# 定义数据库名
DB_NAME="music"
FAVORITES_TABLE="favorites"
USERS_TABLE="users"

# 默认用户
DEFAULT_USER="root"
DEFAULT_PASS="123456"

# 初始化数据库（创建必要的表）
init_db() {
    mysql --defaults-file="$MYSQL_CREDENTIALS" "$DB_NAME" -e "
    CREATE TABLE IF NOT EXISTS $USERS_TABLE (
        username VARCHAR(50) PRIMARY KEY,
        password VARCHAR(50)
    );
    INSERT IGNORE INTO $USERS_TABLE (username, password) VALUES ('$DEFAULT_USER', '$DEFAULT_PASS');

    CREATE TABLE IF NOT EXISTS $FAVORITES_TABLE (
        username VARCHAR(50),
        song_id INT,
        FOREIGN KEY (username) REFERENCES $USERS_TABLE(username),
        FOREIGN KEY (song_id) REFERENCES songs(id)
    );"
}

# 用户登录
login() {
    exec 3>&1
    USERNAME=$(dialog --inputbox "用户名：" 8 40 2>&1 1>&3)
    PASSWORD=$(dialog --passwordbox "密码：" 8 40 2>&1 1>&3)
    exec 3>&-
    
    if [ -z "$USERNAME" ] || [ -z "$PASSWORD" ]; then
        dialog --title "错误" --msgbox "用户名或密码不能为空。" 5 40
        login
    fi

    USER_EXISTS=$(mysql --defaults-file="$MYSQL_CREDENTIALS" "$DB_NAME" -sN -e "SELECT COUNT(*) FROM $USERS_TABLE WHERE username='$USERNAME' AND password='$PASSWORD';")
    if [ "$USER_EXISTS" -eq 1 ]; then
        CURRENT_USER="$USERNAME"
    else
        dialog --title "错误" --msgbox "用户名或密码错误。" 5 40
        login
    fi
}

# 用户注册
register() {
    exec 3>&1
    USERNAME=$(dialog --inputbox "用户名：" 8 40 2>&1 1>&3)
    PASSWORD=$(dialog --passwordbox "密码：" 8 40 2>&1 1>&3)
    exec 3>&-

    if [ -z "$USERNAME" ] || [ -z "$PASSWORD" ]; then
        dialog --title "错误" --msgbox "用户名或密码不能为空。" 5 40
        register
    fi

    USER_EXISTS=$(mysql --defaults-file="$MYSQL_CREDENTIALS" "$DB_NAME" -sN -e "SELECT COUNT(*) FROM $USERS_TABLE WHERE username='$USERNAME';")
    if [ "$USER_EXISTS" -eq 0 ]; then
        mysql --defaults-file="$MYSQL_CREDENTIALS" "$DB_NAME" -e "INSERT INTO $USERS_TABLE (username, password) VALUES ('$USERNAME', '$PASSWORD');"
        dialog --title "成功" --msgbox "注册成功。" 5 40
    else
        dialog --title "错误" --msgbox "用户名已存在。" 5 40
        register
    fi
}

# 获取歌曲列表
get_song_list() {
    dialog --title "可用的歌曲" --cancel-label "返回" --ok-label "选择" \
           --menu "请选择歌曲：" 15 50 4 \
           $(mysql --defaults-file="$MYSQL_CREDENTIALS" "$DB_NAME" -e "SELECT id, title FROM songs;" | awk '{print $1 " " $2}') 2> song_id.txt
}

# 搜索歌曲
search_songs() {
    exec 3>&1
    search_term=$(dialog --inputbox "请输入搜索词：" 8 40 2>&1 1>&3)
    exec 3>&-
    dialog --title "搜索结果" --cancel-label "返回" --ok-label "选择" \
           --menu "以下是搜索结果：" 15 50 4 \
           $(mysql --defaults-file="$MYSQL_CREDENTIALS" "$DB_NAME" -e "SELECT id, title FROM songs WHERE title LIKE '%$search_term%';" | awk '{print $1 " " $2}') 2> song_id.txt
}

# 播放选定的歌曲
play_song() {
    song_id=$(<song_id.txt)
    [ -z "$song_id" ] && return
    song_path=$(mysql --defaults-file="$MYSQL_CREDENTIALS" "$DB_NAME" -sN -e "SELECT filepath FROM songs WHERE id=$song_id;")
    if [ -n "$song_path" ]; then
        dialog --title "播放中" --infobox "正在播放: $song_path" 5 70
        mplayer -quiet "$song_path"
        # 增加播放次数
        mysql --defaults-file="$MYSQL_CREDENTIALS" "$DB_NAME" -e "UPDATE songs SET play_count = play_count + 1 WHERE id=$song_id;"
    else
        dialog --title "错误" --msgbox "歌曲未找到。" 5 40
    fi
}

# 展示最喜欢的歌曲
show_favorite_songs() {
    favorites=$(mysql --defaults-file="$MYSQL_CREDENTIALS" "$DB_NAME" -e "SELECT s.title FROM $FAVORITES_TABLE f JOIN songs s ON f.song_id = s.id WHERE f.username='$CURRENT_USER';")
    if [ -z "$favorites" ]; then
        dialog --title "最喜欢的歌曲" --msgbox "没有最喜欢的歌曲。" 5 40
    else
        dialog --title "最喜欢的歌曲" --msgbox "$favorites" 15 50
    fi
}

# 添加到最喜欢的歌曲
add_to_favorites() {
    get_song_list
    song_id=$(<song_id.txt)
    [ -z "$song_id" ] && return
    mysql --defaults-file="$MYSQL_CREDENTIALS" "$DB_NAME" -e "INSERT INTO $FAVORITES_TABLE (username, song_id) VALUES ('$CURRENT_USER', $song_id);"
    dialog --title "成功" --msgbox "歌曲已添加到最喜欢列表。" 5 40
}

# 删除最喜欢的歌曲
remove_from_favorites() {
    favorites=$(mysql --defaults-file="$MYSQL_CREDENTIALS" "$DB_NAME" -e "SELECT s.id, s.title FROM $FAVORITES_TABLE f JOIN songs s ON f.song_id = s.id WHERE f.username='$CURRENT_USER';" | awk '{print $1 " " $2}')
    if [ -z "$favorites" ]; then
        dialog --title "最喜欢的歌曲" --msgbox "没有最喜欢的歌曲。" 5 40
    else
        dialog --title "删除最喜欢的歌曲" --menu "请选择要删除的歌曲：" 15 50 4 $favorites 2> song_id.txt
        song_id=$(<song_id.txt)
        [ -z "$song_id" ] && return
        mysql --defaults-file="$MYSQL_CREDENTIALS" "$DB_NAME" -e "DELETE FROM $FAVORITES_TABLE WHERE username='$CURRENT_USER' AND song_id=$song_id;"
        dialog --title "成功" --msgbox "歌曲已从最喜欢列表中删除。" 5 40
    fi
}

# 展示所有的歌曲播放记录
show_play_history() {
    dialog --title "所有的歌曲播放记录" --msgbox "$(mysql --defaults-file="$MYSQL_CREDENTIALS" "$DB_NAME" -e "SELECT id, title, play_count FROM songs ORDER BY id;")" 20 70
}

# 选择播放模式
select_play_mode() {
    dialog --title "选择播放模式" --menu "请选择播放模式：" 15 50 4 \
        1 "单曲循环" \
        2 "顺序播放" \
        3 "随机播放" 2> mode.txt
    mode=$(<mode.txt)

    # 获取用户选择的歌曲ID
    read -p "请输入歌曲ID： " song_id
    local song_path=$(get_song_path "$song_id")

    case $mode in
        1)
            echo "您选择了单曲循环。"
            single_loop "$song_id"
            ;;
        2)
            echo "您选择了顺序播放。"
            sequential_play
            ;;
        3)
            echo "您选择了随机播放。"
            random_play
            ;;
    esac
}

# 获取歌曲路径
get_song_path() {
    local song_id=$1
    local song_path=$(mysql --defaults-file="$MYSQL_CREDENTIALS" "$DB_NAME" -sN -e "SELECT filepath FROM songs WHERE id=$song_id;")
    echo $song_path
}

# 单曲循环
single_loop() {
    local song_id=$1
    local song_path=$(get_song_path "$song_id")
    while true; do
        mplayer -quiet "$song_path"
        # 增加播放次数
        mysql --defaults-file="$MYSQL_CREDENTIALS" "$DB_NAME" -e "UPDATE songs SET play_count = play_count + 1 WHERE id=$song_id;"
        read -n 1 -s -r -p "按任意键继续单曲循环，或按Ctrl+C退出。"
        echo
    done
}

# 顺序播放
sequential_play() {
    local -a song_ids=($(mysql --defaults-file="$MYSQL_CREDENTIALS" "$DB_NAME" -sN -e "SELECT id FROM songs;"))
    for song_id in "${song_ids[@]}"; do
        local song_path=$(get_song_path "$song_id")
        mplayer -quiet "$song_path"
        # 增加播放次数
        mysql --defaults-file="$MYSQL_CREDENTIALS" "$DB_NAME" -e "UPDATE songs SET play_count = play_count + 1 WHERE id=$song_id;"
    done
}

# 随机播放
random_play() {
    local -a song_ids=($(mysql --defaults-file="$MYSQL_CREDENTIALS" "$DB_NAME" -sN -e "SELECT id FROM songs;"))
    local -a random_order=( $(shuf -i 0-$((${#song_ids[@]}-1))) )
    for i in "${random_order[@]}"; do
        local song_id=${song_ids[$i]}
        local song_path=$(get_song_path "$song_id")
        mplayer -quiet "$song_path"
        # 增加播放次数
        mysql --defaults-file="$MYSQL_CREDENTIALS" "$DB_NAME" -e "UPDATE songs SET play_count = play_count + 1 WHERE id=$song_id;"
    done
}

# 添加歌曲
add_song() {
    exec 3>&1
    song_path=$(dialog --title "添加歌曲（空格键选择歌曲）" --fselect /home/ 14 48 2>&1 1>&3)
    exec 3>&-
    # 使用basename和cut命令去除.mp3后缀
    song_title=$(basename "$song_path" | cut -d '.' -f 1)
    mysql --defaults-file="$MYSQL_CREDENTIALS" "$DB_NAME" -e "INSERT INTO songs (title, filepath) VALUES ('$song_title', '$song_path');"
    if [ $? -eq 0 ]; then
        dialog --title "成功" --msgbox "歌曲添加成功。" 5 40
    else
        dialog --title "错误" --msgbox "歌曲添加失败。" 5 40
    fi
}

# 删除歌曲
delete_song() {
    if [ "$CURRENT_USER" != "$DEFAULT_USER" ]; then
        dialog --title "错误" --msgbox "只有root用户可以删除歌曲。" 5 40
        return
    fi
    get_song_list
    song_id=$(<song_id.txt)
    [ -z "$song_id" ] && return
    mysql --defaults-file="$MYSQL_CREDENTIALS" "$DB_NAME" -e "DELETE FROM songs WHERE id=$song_id;"
    if [ $? -eq 0 ]; then
        dialog --title "成功" --msgbox "歌曲删除成功。" 5 40
    else
        dialog --title "错误" --msgbox "歌曲删除失败。" 5 40
    fi
}

# 用户管理
manage_users() {
    if [ "$CURRENT_USER" != "$DEFAULT_USER" ]; then
        dialog --title "错误" --msgbox "只有root用户可以管理用户。" 5 40
        return
    fi
    exec 3>&1
    username=$(dialog --inputbox "请输入要删除的用户名：" 8 40 2>&1 1>&3)
    exec 3>&-

    if [ -z "$username" ]; then
        dialog --title "错误" --msgbox "用户名不能为空。" 5 40
        return
    fi

    if [ "$username" == "$DEFAULT_USER" ]; then
        dialog --title "错误" --msgbox "不能删除root用户。" 5 40
        return
    fi

    mysql --defaults-file="$MYSQL_CREDENTIALS" "$DB_NAME" -e "DELETE FROM $USERS_TABLE WHERE username='$username';"
    mysql --defaults-file="$MYSQL_CREDENTIALS" "$DB_NAME" -e "DELETE FROM $FAVORITES_TABLE WHERE username='$username';"
    if [ $? -eq 0 ]; then
        dialog --title "成功" --msgbox "用户删除成功。" 5 40
    else
        dialog --title "错误" --msgbox "用户删除失败。" 5 40
    fi
}

# 主界面
main_menu() {
    while true; do
        exec 3>&1
        selection=$(dialog --title "音乐播放器" --cancel-label "退出" --menu "请选择操作：" 15 50 9 \
            1 "播放音乐" \
            2 "搜索音乐" \
            3 "显示播放列表" \
            4 "最喜欢的歌曲" \
            5 "显示播放记录" \
            6 "选择播放模式" \
            7 "添加歌曲" \
            8 "删除歌曲" \
            9 "用户管理" 2>&1 1>&3)
        exit_status=$?
        exec 3>&-
        case $exit_status in
            1) clear; exit ;;
        esac
        case $selection in
            1) get_song_list; play_song ;;
            2) search_songs; play_song ;;
            3) get_song_list ;;
            4)
                exec 3>&1
                fav_selection=$(dialog --title "最喜欢的歌曲" --menu "请选择操作：" 15 50 3 \
                    1 "查看最喜欢的歌曲" \
                    2 "添加到最喜欢的歌曲" \
                    3 "删除最喜欢的歌曲" 2>&1 1>&3)
                exec 3>&-
                case $fav_selection in
                    1) show_favorite_songs ;;
                    2) add_to_favorites ;;
                    3) remove_from_favorites ;;
                esac
                ;;
            5) show_play_history ;;
            6) select_play_mode ;;
            7) add_song ;;
            8) delete_song ;;
            9) manage_users ;;
        esac
    done
}

# 初始化数据库
init_db

# 登录或注册
exec 3>&1
choice=$(dialog --title "欢迎" --menu "请选择操作：" 15 50 2 \
    1 "登录" \
    2 "注册" 2>&1 1>&3)
exec 3>&-

case $choice in
    1) login ;;
    2) register; login ;;
esac

# 进入主菜单
main_menu
