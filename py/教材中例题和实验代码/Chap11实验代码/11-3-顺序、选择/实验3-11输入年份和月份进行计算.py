y=int(input("请输入年份:"))
m=int(input("请输入月份:"))
if 1000<=y<=2100 and 1<=m<=12:
    if y % 4 ==0 and y % 100 != 0 or y % 400 == 0:
        leapyear=True
        print("{}年是闰年".format(y))
    else:
        leapyear=False
        print("{}年不是闰年".format(y))
    if m in [1,2,3]:
        jidu="一季度"
    if m in [4,5,6]:
        jidu="二季度"
    if m in [7,8,9]:
        jidu="三季度"
    if m in [10,11,12]:
        jidu="四季度"
    print("{}月是第{}".format(m,jidu))
    if m in [1,3,5,7,8,10,12]:
        day=31
    if m==2:
        if leapyear==True:
            day=29
        else:
            day=28
    if m in [4,6,9,11]:
        day=30
    print("{}月有{}天".format(m,day))
else:
    print("输入的年份或月份不合法！")
        

