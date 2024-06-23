pi=0
n=1
t=1
while abs(t)>=0.0000001:
    pi=pi+t
    n=n+1
    t=(-1)**(n-1)/(2*n-1)
pi=4*pi
print("π的近似值为:",pi)
