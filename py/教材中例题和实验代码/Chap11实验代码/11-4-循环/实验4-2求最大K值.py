N=int(input("请输入正整数N:"))
s=0
k=0
while s<N:
    k=k+1
    s=s+k*k
#    print(k,s)
print("1+2*2+3*3+…<{}的最大K值是{}".format(N,k-1))

