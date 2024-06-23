def ssum(n):
    ss=0
    for i in range(1,n+1):
        ss=ss+i
    return ss
n=int(input("请输入需要求和的项数n："))
s=0
for i in range(1,n+1):
    s=s+ssum(i)
print("求得的和为：",s)

