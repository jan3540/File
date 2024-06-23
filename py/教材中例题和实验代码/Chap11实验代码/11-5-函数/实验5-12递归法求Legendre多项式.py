def Pnx(n,x):
    if n==0:
        return 1
    elif n==1:
        return x
    else:
        return ((2*n-1)*x*Pnx(n-1,x)-(n-1)*Pnx(n-2,x))/n

n=int(input("请输入Legendre多项式的项数n："))
x=eval(input("请输入x(|x|<=1)："))
print("Legendre多项式的值：",Pnx(n,x))

