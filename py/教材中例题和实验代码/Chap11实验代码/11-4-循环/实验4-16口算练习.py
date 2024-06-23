from random import randint
while True:
    a=randint(0,9)
    b=randint(0,9)
    print("{}+{}=?".format(a,b))
    x=input("请输入两个数的和,退出请输入q:")
    if x=='q':
        break
    if int(x)==a+b:
        print("运算正确！")
    else:
        print("{}+{}={}，您的运算错误，继续努力！".format(a,b,a+b))
