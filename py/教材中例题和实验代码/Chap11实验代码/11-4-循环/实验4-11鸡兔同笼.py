M=int(input("请输入鸡和兔的总只数:"))
N=int(input("请输入鸡和兔的总脚数:"))
if N % 2 != 0:
    print("输入的脚数为奇数，不合理！")
else:
    for x in range(M+1):
        y=M-x
        if 2*x+4*y==N:
            print("鸡有{}只，兔有{}只".format(x,y))
            break
    else:
        print("输入的数据不合理！")
