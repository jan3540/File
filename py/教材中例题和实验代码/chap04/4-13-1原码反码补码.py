def sourceCode(m):                   # 原码
    n=abs(m)
    bincode=''
    while n!=0:                      # 转二进制
        bincode = str(n%2) + bincode 
        n=n//2
    if m>0:                          # 16位，sc是原码变量
        sc='0'+'0'*(15-len(bincode))+bincode  # 最高位的0表示正
    else:
        sc='1'+'0'*(15-len(bincode))+bincode  # 最高位的1表示负
    return sc

def inverseCode(ch):                 # 反码
    if ch[0]=='0':
        return ch                    # 正数的反码等于原码
    else:
        ic='1'                       # ic是负数的反码变量，最高位是1
        for i in range(1,16):        # 求负数的反码
            if ch[i]=='0':
                ic=ic+'1'
            else:
                ic=ic+'0'
        return ic

def complement(ch):                  # 补码
    if ch[0]=='0':    
        return ch                    # 正数的补码、原码、反码相等
    else:
        x=1                          # x是要加的1，后面表示进位
        com=''                       # com是负数的补码变量
        for i in range(15,-1,-1):    # 从低位向高位遍历
            y=int(ch[i])+x
            if y==2:
                x=1                  # 有进位
                com='0'+com
            else:
                x=0                  # 无进位
                com=str(y)+com
        return com
                
if __name__=="__main__":
    m=int(input("请输入一个非0整数："))
    sc=sourceCode(m)                 # 调用求原码
    ic=inverseCode(sc)               # 调用求反码
    com=complement(ic)               # 调用求补码
    print("{} 的原码是 {}".format(m,sc))
    print("{} 的反码是 {}".format(m,ic))
    print("{} 的补码是 {}".format(m,com))

