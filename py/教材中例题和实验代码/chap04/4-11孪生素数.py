import prime2to100 as p
k=0
for m in range(1,101):
    if p.prime(m)==True and p.prime(m+2)==True:
        k=k+1
        print("第{}对孪生素数：{} 和 {}".format(k,m,m+2))
