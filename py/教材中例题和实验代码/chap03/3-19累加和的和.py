n=int(input("请输入需要求和的项数n："))
s=0
for i in range(1,n+1):
    s1=0                   # 注意该语句的位置及作用
    for j in range(1,i+1):
        s1=s1+j
    s=s+s1
print("求得的和为：",s)

