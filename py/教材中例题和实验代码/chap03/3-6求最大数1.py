a,b,c=eval(input("请输入3个整数(用逗号分隔)："))
if a>b:
    if a>c:
        maxnum=a
    else:
        maxnum=c
else:
    if b>c:
        maxnum=b
    else:
        maxnum=c
print("最大的数是：",maxnum)


#maxnum=(a if a>c else c) if a>b else (b if b>c else c)

#print("最大的数是：",maxnum)

