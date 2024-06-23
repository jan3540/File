def chb(n,x):                             # 递归函数定义
    if n==0:
        return 1
    elif n==1:
        return x
    else:
        return 2*x*chb(n-1,x)-chb(n-2,x)  # 递归调用
    
n=eval(input("请输入项数n:"))
x=eval(input("请输入x值："))
T=chb(n,x)                                # 函数调用
print("切比雪夫多项式的值是{}".format(T))


