import random
import math
def redP(n=20, m=200):                # n是红包个数，m是红包总金额
    red_packet = []                   # 创建红包空列表
    for i in range(1,n):              # 循环n-1次，产生n-1个红包
        maxmoney = m/(n-(i-1))*2      # 第i个红包可能的最大值
        get_money = math.floor(random.uniform(0.01,maxmoney)*100)/100
                                      # 生成第i个红包的金额
        #get_money = round(random.uniform(0.01,maxmoney),2)
        red_packet.append(get_money)  # 向列表中添加第i个红包
        m = m - get_money             # 红包剩余金额
    red_packet.append(round(m, 2))    # 向列表中添加最后一个红包
    return red_packet                 # 返回红包列表

if __name__=="__main__":
    number = int(input('请输入红包个数：'))
    money = float(input('请输入红包总金额：'))
    if money>=number*0.01:
        print("生成的红包列表:",redP(number, money))  
    else:
        print("钱少于人头数，请重新输入！")



