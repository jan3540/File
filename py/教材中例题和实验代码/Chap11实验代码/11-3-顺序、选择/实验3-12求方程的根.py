from math import sqrt
a,b,c=eval(input("请输入一元二次方程的系数:"))
if a==0 and b==0:
    print("方程无意义")
elif a==0 and b!=0:
    x=-c/b
    print("方程有一个根:",format(x,".2f"))
else:
    delt=b*b-4*a*c
    if delt>0:
        x1=(-b+sqrt(delt))/(2*a)
        x2=(-b-sqrt(delt))/(2*a)
        print("方程有两个不等实根:x1={:.2f},x2={:.2f}".format(x1,x2))
    elif delt==0:
        x1=x2=-b/(2*a)
        print("方程有两个相等实根:x1={:.2f},x2={:.2f}".format(x1,x2))
    else:
        x1=complex(round(-b/(2*a),2),round(sqrt(-delt)/(2*a),2))
        x2=complex(round(-b/(2*a),2),round(-sqrt(-delt)/(2*a),2))
        print("方程有两个不等虚根:x1={},x2={}".format(x1,x2))
        
