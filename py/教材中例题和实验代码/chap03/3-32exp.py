x=eval(input("请输入x:"))
t=x             # 第一项的值
n=1             # 第一项
s=1             # s是累加和变量
eps=0.000001    # 定义一个比较小的数
while abs(t)>=eps:
    s=s+t       # 前n项累加和
    n=n+1
    t=t*x/n     # 利用递推公式求得下一项
print("e**{}={:.6f}".format(x,s))
'''
t=1             # 第一项的值
n=1             # 第一项
s=0             # s是累加和变量
eps=0.000001    # 定义一个比较小的数
x=eval(input("请输入x:"))
while abs(t)>=eps:
    s=s+t       # 前n项累加和
    t=t*x/n     # 利用递推公式求得下一项
    n=n+1
print("e**{}={:.6f}".format(x,s))'''

    
