from datetime import datetime
#d=datetime.now()
d=datetime(2023,10,14,12,46,57)
print("第一种输出格式:",d.strftime("%Y年%m月%d日 %I:%M:%S %p"))
print("第二种输出格式:",d.strftime("%Y/%m/%d %H:%M:%S"))
print("第三种输出格式:",d.strftime("%Y-%m-%d %A %I:%M:%S %p"))

y=d.year
if y%4==0 and y%100!=0 or y%400==0:
    print(y,"年是闰年",sep='')
else:
    print(y,"年不是闰年",sep='')

t=d-datetime(2023,1,1)      # t是timedelta对象
dd=t.days+1
print("{}年{}月{}日是{}年的第{}天".format(d.year,d.month,d.day,d.year,dd))
print()
