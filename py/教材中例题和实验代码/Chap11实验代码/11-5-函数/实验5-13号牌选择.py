import random
def Vehicle_number():
    c="某"
    c=c+random.choice(['A','B','C','D'])+'-'          
    lst1=list(map(str,range(10)))                      # 生成10个数字字符的列表
    lst2=[chr(i) for i in range(65,91)]                # 生成26个大写字符的列表
    lst2=list(filter(lambda x: x!='O' and x!='I',lst2)) # 去掉大写字母O和I的列表
    for i in random.sample(lst1+lst2,3):               # 在随机生成的3个字符列表中取
        c=c+i                                          # 字符串连接运算
    c=c+random.choice(lst1)+random.choice(lst1)        # 连接第4位和第5位随机产生的数字
    return c                                           # 返回车牌号

if __name__=="__main__":
    mylst=[]
    for i in range(10):
        mylst.append(Vehicle_number())                 # 调用创建车牌号列表
    for i in range(len(mylst)):
        print("{:2d}:{}".format(i+1,mylst[i]))         # 输出序号和车牌号
    num=int(input("请输入心仪号牌序号:"))              # 输入选择的序号
    print("您选中的号牌为:",mylst[num-1])              # 输出序号对应的车牌号
