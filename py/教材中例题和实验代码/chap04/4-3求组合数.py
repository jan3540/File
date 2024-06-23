def fac(n):
    f=1
    for i in range(1,n+1):
        f=f*i
    return f
m,n=eval(input("请输入m和n的值(m>=n):"))
print("组合数为:",fac(m)//fac(n)//fac(m-n))


