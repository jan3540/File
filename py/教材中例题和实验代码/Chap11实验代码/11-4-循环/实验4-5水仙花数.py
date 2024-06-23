# 三重循环
print("求出的所有水仙花数有：")
for a in range(1,10):
    for b in range(10):
        for c in range(10):
            k=a*100+b*10+c
            if a**3+b**3+c**3==k:
                print(k,end=' ')
print()

# 一重循环
for i in range(100,1000):
    a=i//100
    b=i//10%10
    c=i%10
    if i==a**3+b**3+c**3:
        print(i,end=' ')
print()
    
# 列表解析
f=[a*100+b*10+c for a in range(1,10) for b in range(0,10) for c in range(0,10) if a*100+b*10+c==a**3+b**3+c**3]
print(f)
