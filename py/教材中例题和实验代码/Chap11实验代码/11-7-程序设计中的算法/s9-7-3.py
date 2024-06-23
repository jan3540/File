def yueSeFu(m,n,k):
    serial_num = list(range(1,m +1))    # 创建从1到m的序号
    index = 0
    if k==1:
        for i in range(1,n+1):
            serial_num.remove(i)
            print('{0}号下船了'.format(i))
    else:
        while len(serial_num) > m - n:
            for i in serial_num:            # 遍历每个编号
                index += 1                     
                if index == k:                # 当外部变量index找到k时，进行下面代码块的操作
                    serial_num.remove(i)    # 移除需要下船的人的编号
                    index = 1                # 这时候index已经找到序号k了，就要重新遍历
                    print('{0}号下船了'.format(i))
                    if len(serial_num) == m - n:
                        break
if __name__ == '__main__':
    # 传入起始人数m，需要下船的人数n，数到多少下船的序号k
    yueSeFu(30,15,9)
