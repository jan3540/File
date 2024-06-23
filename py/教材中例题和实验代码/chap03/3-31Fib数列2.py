n=int(input("请输入Fibonacci数列的项数n："))
f1=f2=1
print(f1,f2,sep=',',end=',')
for i in range(3,n+1):
    f1,f2=f2,f1+f2
    print(f2,end=',')
    
