def f():
    a=100    # 定义局部变量a
    b=200    # 定义局部变量b
    print("   函数中a和b的值为：{}和{}".format(a,b)) 
x=10         # 定义全局变量x
y=20         # 定义全局变量y
print("     x和y的原始值为：{}和{}".format(x,y))
f()
print("调用f函数后x和y的为：{}和{}".format(x,y))
