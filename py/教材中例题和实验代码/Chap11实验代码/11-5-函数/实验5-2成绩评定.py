def passed(x):
    if 0<=x<60:
        print("该同学成绩不合格，需继续努力！")
    elif 60<=x<=100:
        print("该同学成绩合格啦！")
    else:
        print("输入的成绩错误！")

score=int(input("请输入一个分数:"))
passed(score)
