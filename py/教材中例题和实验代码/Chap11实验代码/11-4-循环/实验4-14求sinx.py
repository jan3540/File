# 求sin(x)
x=eval(input("输入x(弧度)："))
s=0
t=x
n=1
while abs(t)>=1e-6:
    s=s+t
    n=n+1
    t=t*(-x*x)/((2*n-2)*(2*n-1))
print("sin({})的近似值为：{}".format(x,s))

                    
