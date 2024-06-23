def tranDec(m,n):
    base=['0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F']
    if m<n:
        return str(m)
    else:
        return tranDec(m//n,n)+base[m%n]

if __name__=="__main__":
    num=int(input("请输入第一个数："))
    base=int(input("请输入第二个数："))
    print(tranDec(num,base))



