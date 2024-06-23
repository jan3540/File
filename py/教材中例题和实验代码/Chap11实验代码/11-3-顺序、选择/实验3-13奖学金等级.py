m1,m2,m3=eval(input("请输入三门功课成绩:"))
ave=(m1+m2+m3)/3
if ave>95 or m1==m2==100 and m3>=80 or \
             m1==m3==100 and m2>=80 or \
             m2==m3==100 and m1>=80:
    print("该同学获得一等奖学金。")
elif ave>90 or m1==100 and m2>=75 and m3>=75 \
            or m2==100 and m1>=75 and m3>=75 \
            or m3==100 and m1>=75 and m2>=75:
    print("该同学获得二等奖学金。")
elif m1>=70 and m2>=70 and m3>=70:
    print("该同学获得三等奖学金。")
else:
    print("该同学没有获得奖学金。")
