n=int(input("请输入一个正整数："))
count=0             # count变量用于统计n的位数
while n>0:
    count=count+1   
    n=n//10         # 整除运算其目的是循环一次去调n的最低位数字
print("该数是{}位数".format(count))
