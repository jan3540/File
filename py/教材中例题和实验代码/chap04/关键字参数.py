import math
def length(x1,y1,x2,y2):
    L=math.sqrt((x1-x2)**2+(y1-y2)**2)
    return L

print(length(0,0,3,4))              # 位置参数
print(length(x1=0,x2=3,y1=0,y2=4))  # 关键字参数
