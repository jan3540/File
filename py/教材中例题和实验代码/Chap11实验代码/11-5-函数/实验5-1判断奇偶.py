def jiou(x):
    if x % 2 != 0:
        return True
    else:
        return False

x=int(input("请输入一个整数:"))
if jiou(x)==True:
    print(x,"是奇数",sep="")
else:
    print(x,"是偶数",sep="")
