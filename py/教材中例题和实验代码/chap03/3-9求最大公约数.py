m=eval(input("请输入正整数m："))
n=eval(input("请输入正整数n："))
if m<n:
    m,n=n,m
r=m%n
while r!=0:
    m=n
    n=r
    r=m%n
print("最大公约数是：",n)



