def Fac(n):                          # 递归函数定义
    if n==0 or n==1:
        return 1
    else:
        return n*Fac(n-1)            # 递归调用
    
n=eval(input("请输入一个非负整数:"))
F=Fac(n)                             # 函数调用
print("{}!={}".format(n,F))


