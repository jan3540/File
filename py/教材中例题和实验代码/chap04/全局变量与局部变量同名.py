def f():
    x=100    # 定义局部变量x
    y=200    # 定义局部变量y
    print("   函数中x和y的值为：{}和{}".format(x,y)) 
x=10         # 定义全局变量x
y=20         # 定义全局变量y
print("     x和y的原始值为：{}和{}".format(x,y))
f()
print("调用f函数后x和y的为：{}和{}".format(x,y))


        
    
