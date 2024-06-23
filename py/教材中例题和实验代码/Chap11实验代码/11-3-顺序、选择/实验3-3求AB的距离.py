import math
x1,y1=eval(input("请输入A点的坐标:"))
x2,y2=eval(input("请输入B点的坐标:"))
AB=math.sqrt((x1-x2)**2+(y1-y2)**2)
print("A({},{})与B({},{})两点的距离是:{:.2f}".format(x1,y1,x2,y2,AB))
