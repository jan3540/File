import csv

# 读取原始数据
with open('sy8-2.csv', 'r', newline='', encoding='gbk') as file:
    reader = csv.reader(file)
    data = list(reader)
# 添加表头
data.insert(0, ['姓名', '班级', '语文', '数学', '英语'])

# 写入带有表头的数据
with open('sy8-2.csv', 'w', newline='', encoding='gbk') as file:
    writer = csv.writer(file)
    writer.writerows(data)

print("已将表头写入sy8-2.csv文件。")