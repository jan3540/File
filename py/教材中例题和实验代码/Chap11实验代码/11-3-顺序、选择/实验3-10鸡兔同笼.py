'''
鸡x、兔y，则有方程组 x+y=M
                     2x+4y=N

'''
M=int(input("请输入鸡和兔的总只数:"))
N=int(input("请输入鸡和兔的总脚数:"))
if N % 2 != 0:
    print("输入的脚数为奇数，不合理！")
else:
    x=2*M-N//2
    y=M-x
    if x<0 or y<0 :
        print("求出的只数为负，输入的数据不合理！")
    else:
        print("鸡有{}只，兔有{}只".format(x,y))
