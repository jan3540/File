import math
a,b,c=eval(input("请输入三角形的3边长(用逗号分隔):"))
if a>0 and b>0 and c>0:
    if a+b>c and a+c>b and b+c>a:
        p=(a+b+c)/2
        S=math.sqrt(p*(p-a)*(p-b)*(p-c))
        print("三角形的面积是:{:.2f}。".format(S))
    else:
        print("输入的边长不能构成三角形！")
else:
    print("输入的边长数据无效！")

    


