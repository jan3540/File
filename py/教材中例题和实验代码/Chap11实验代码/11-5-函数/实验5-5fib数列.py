def fib(n):
    f=[1]*n
    for i in range(2,n):
        f[i]=f[i-1]+f[i-2]
    return f

n=int(input("请输入Fibonacci数列的项数n:"))
flst=fib(n)
print(flst)

