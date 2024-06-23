#求sqrt(a),精确到|xn+1-xn|<1e-6
a=eval(input("输入任意实数a(a>=0):"))
x0=a
while True:
    x1=(x0+a/x0)/2
    if abs(x1-x0)<0.000001:
        print("x的近似值为:",format(x1,".6f"))
        break
    x0=x1
    

                    
