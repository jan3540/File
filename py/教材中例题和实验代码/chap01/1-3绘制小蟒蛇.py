import turtle
#turtle.setup(600,300,200,200)
turtle.penup()
turtle.fd(-250)
turtle.pendown()
turtle.pensize(30)            # 画笔尺寸
turtle.pencolor("red")
#turtle.setheading(-40)              # 前进的方向
turtle.right(40)
for i in range(2):
    turtle.circle(70, 80)
    turtle.circle(-70, 80)
turtle.circle(70, 80/2)
turtle.forward(70/2)          # 直线前进
turtle.circle(15, 180)
turtle.forward(70/4)

