import random
x=random.randint(100,999)
print("生成的随机数是:",x)          
y=input("请输入你猜的数(结束游戏请输入q): ")
while y!="q":
    y=int(y)
    if y>x:
       y=input("您猜大了，请重新输入您猜的数(结束请输入q): ")
    elif y<x:
       y=input("您猜小了，请重新输入您猜的数(结束请输入q): ")
    else :
       print("恭喜您，猜对了！")
       y="q"
print("游戏结束！")


