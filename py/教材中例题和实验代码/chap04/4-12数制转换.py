def tranDec(m,n):
    base=['0','1','2','3','4','5','6','7','8','9',
          'A','B','C','D','E','F']
    trans=""
    while m!=0:
        r = m % n
        trans = base[r] + trans   # trans = trans + base[r]
        m = m // n
    return trans                  # return trans[::-1]

if __name__=="__main__":
    m=eval(input("请输入一个十进制的正整数m："))
    n=eval(input("请输入一个二到十六的整数n："))
    if m>0 and 2<=n<=16:
        t=tranDec(m,n)
        print("十进制数 {} 转换成 {} 进制数是：{}".format(m,n,t))
        #print(f"十进制数 {m} 转换成 {n} 进制数是：{t}")
    else:
        print("输入的数不符合要求！")
