print(" " * 34 +"九九乘法表")  # print("{:^74s}".format("九九乘法表"))
print("=" * 79) 
for i in range(1,10):
    for j in range(1,1+i):
        print("{}×{}={:<2d}".format(i,j,i*j),end="  ")
    print()  # 此处用于换行


    

