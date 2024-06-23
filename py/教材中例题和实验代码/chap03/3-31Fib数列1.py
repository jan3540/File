n=int(input("请输入Fibonacci数列的项数n："))
F=[0]*n                  # 创建有n个元素的列表，且每个元素初值是0
F[0]=F[1]=1
for i in range(2,n):
    F[i]=F[i-1]+F[i-2]   # 根据递推关系求下一项
print(F)
