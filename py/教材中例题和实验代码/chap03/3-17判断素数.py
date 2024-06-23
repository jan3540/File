m=eval(input("请输入一个≥2的正整数："))         
for i in range(2,m):
    if m % i == 0:      
        print("{}不是素数".format(m))
        break 
else:
    print("{}是素数".format(m))


