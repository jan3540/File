import turtle
import math
x1,y1=eval(input("请输入第一个点的坐标："))
x2,y2=eval(input("请输入第二个点的坐标："))
distance=math.sqrt((math.fabs((x1-x2))**2+math.fabs((y2-y1))**2))
# distance=math.sqrt((x1-x2)**2+(y2-y1)**2)
turtle.penup()
turtle.goto(x1,y1)
turtle.pendown()
turtle.write("点1")
turtle.goto(x2,y2)
turtle.write("点2")

turtle.penup()
turtle.goto((x1+x2)/2,(y1+y2)/2)
turtle.write(distance)

turtle.done()
