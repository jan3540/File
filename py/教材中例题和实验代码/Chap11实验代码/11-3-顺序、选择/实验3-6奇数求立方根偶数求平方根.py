x=int(input("请输入一个整数:"))
# 单分支
'''
if x % 2 == 1:
    y=x**(1/3)
if x % 2 == 0:
    y=x**(1/2)
'''
#双分支
'''
if x % 2 == 1:
    y=x**(1/3)
else:
    y=x**(1/2)
'''
# 条件运算
y=x**(1/3) if x%2==1 else x**(1/2)

print("y的值为:",y)
