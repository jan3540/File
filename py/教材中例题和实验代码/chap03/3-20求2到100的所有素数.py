num=0
print("2到100之间的素数有：")
for m in range(2,101):       
    for i in range(2,m):
        if m % i == 0:      
            break 
    else:
        num=num+1
        print(m,end=' ')
        if num % 5 == 0:
            print()


