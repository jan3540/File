print(" " * 34 +"九九乘法表")  # print("{:^74s}".format("九九乘法表"))
print("=" * 79)
lst = [str(i)+'×'+str(j)+'='+str(i*j)+('\n' if i==j else ' ') for i in range(1,10) for j in range(1,i+1)]
for i in lst:
    print(i,end=' ')


'''
for i in range(1,10):
    for j in range(1,10):
        print("{}×{}={:<2d}".format(i,j,i*j),end="  ")
    print()  # 此处用于换行'''


    

