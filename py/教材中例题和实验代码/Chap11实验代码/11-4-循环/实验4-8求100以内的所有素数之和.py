s=0
for i in range(2,100):
    for j in range(2,i):
        if i%j==0:
            break
    else:
        s=s+i
print("100以内的素数之和为:",s)
    
