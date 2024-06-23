def gcd(m,n):   
    if m % n == 0:
        return n
    else:
        return gcd(n,m % n)

m,n=eval(input("请输入正整数m和n："))
if m<n:
    m,n=n,m
print("最大公约数是：",gcd(m,n))



