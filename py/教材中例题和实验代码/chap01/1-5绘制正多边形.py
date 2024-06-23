import turtle 
turtle.screensize(600,500,'white') 
turtle.pensize(3)              # 设置画笔宽度为3 
turtle.pencolor('blue')          # 设置画笔颜色为黑色 
turtle.fillcolor('yellow')        # 设置填充颜色为黄色 
turtle.begin_fill()             # 开始填充
turtle.penup()
turtle.forward(-300)
turtle.pendown()
for i in range(3,10000):            # 循环6次
    turtle.circle(30, steps=i)    # 画正i边形
    turtle.forward(100)        
turtle.circle(30)               # 画圆
turtle.end_fill()               # 结束填充
turtle.hideturtle()
turtle.done()
