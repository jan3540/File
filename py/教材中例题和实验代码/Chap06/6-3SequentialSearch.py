a = [8, -3, 14, 7, 9]
k = -1 # 记录下标
print("已有数据如下：")
for i in a:
    print(i, end=" ") # 输出数原数据序列
print()
m = int(input("请输入想要查找的数m：")) # 变量m为要查找的整数
flag=False
for i in range(len(a)):
    if m==a[i]:
        flag=True
        k=i
        break
if flag==True:
    print("m = {}, index = {}".format(m,k))
else:
    print("没找到!")
