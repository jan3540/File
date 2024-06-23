f1,f2,f3=1,2,3
i=4
while True:
    f=f1+f2+f3
    print(i,f)
    if f>2000:
        print("数列从第{}项开始，数值超过2000。".format(i))
        print("第{}项的值为{}。".format(i,f))
        break
    f1,f2,f3=f2,f3,f    #等价于:f1=f2;f2=f3;f3=f
    i=i+1
    
    
