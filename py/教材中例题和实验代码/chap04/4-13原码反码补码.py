def sourceCode(m):                   # 原码函数定义
    n=abs(m)
    bincode=''
    while n!=0:                      # while循环完成十进制转二进制
        bincode = str(n%2) + bincode 
        n=n//2
    if m>0:                          # if结构处理16位的原码，sc是原码变量
        sc='0'+'0'*(15-len(bincode))+bincode  # 最前面的0表示正
    else:
        sc='1'+'0'*(15-len(bincode))+bincode  # 最前面的1表示负
    return sc

def inverseCode(m):                  # 反码函数定义
    ch=sourceCode(m)                 # 调用求原码，是嵌套调用
    if ch[0]=='0':
        return ch                    # 正数的反码等于原码
    else:
        ic='1'                       # ic是负数的反码变量，最高位是1
        for i in range(1,16):        # for循环求负数的反码
            if ch[i]=='0':
                ic=ic+'1'
            else:
                ic=ic+'0'
        return ic

def complement(m):                   # 补码函数定义
    ch=inverseCode(m)                # 调用求反码，是嵌套调用
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
                com=ch[:i]+com       # 无进位后，剩余高位无需再计算，取出与已算出的低位连接
                break                # 提前结束for循环
        return com
                
if __name__=="__main__":
    m=int(input("请输入一个非0整数："))
    if -32767<=m<=32767 and m!=0:
        sc=sourceCode(m)                 # 调用原码函数
        ic=inverseCode(m)                # 调用反码函数
        com=complement(m)                # 调用补码函数
        print("{} 的原码是 {}".format(m,sc))
        print("{} 的反码是 {}".format(m,ic))
        print("{} 的补码是 {}".format(m,com))
    else:
        print("输入的整数不符合程序的要求，请重输...")

