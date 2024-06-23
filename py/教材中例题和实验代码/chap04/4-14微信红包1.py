import random
import math
def redP(n=20, m=200):
    red_packet = []
    for i in range(1,n):                            
        maxmoney = m/(n-(i-1))*2                     
        get_money =math.floor(random.uniform(0.01, maxmoney)*100)/100   
        red_packet.append(get_money)                 
        m = m - get_money                           
    red_packet.append(round(m, 2))                  
    return red_packet                               

if __name__=="__main__":
    number = int(input('请输入红包个数：'))
    money = float(input('请输入红包总金额：'))
    if money>=number*0.01:
        print("生成的红包列表:",redP(number, money))   
    else:
        print("钱少于人头数，请重新输入！")


