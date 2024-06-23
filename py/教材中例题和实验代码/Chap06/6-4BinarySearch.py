a = [1, 2, 3, 4, 6, 7, 10, 12]
low = 0 #上界
high = len(a) - 1 #下界
k = -1 # 记录下标
print("有序数据如下：")
for i in a:
    print(i, end=" ") # 输出数原数据序列
print()
key = int(input("请输入想要查找的数key：")) # 变量key为要查找的整数
while low <= high: # 继续查找的控制条件
    mid = (low + high) // 2 # 变量mid为数组序列的中间位置
    if key < a[mid]:
        high = mid - 1
    else:
        if key > a[mid]:
            low = mid + 1
        else:
            k = mid
            break # 一旦找到所要查找的元素便跳出循环
if k!=-1:
    print("key = {}, index = {}".format(key,k))
else:
    print("没找到!")
