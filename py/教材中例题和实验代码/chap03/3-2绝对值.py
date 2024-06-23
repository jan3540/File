x=eval(input("请输入一个数："))
'''if x>=0:
    y=x
else:
    y=-x'''
y=x if x>=0 else -x
print("{}的绝对值是{}".format(x,y))


