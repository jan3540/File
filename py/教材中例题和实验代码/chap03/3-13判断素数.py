m=eval(input("请输入一个≥2的正整数："))
p=True              
for i in range(2,m):
    if m % i == 0:  
        p=False     
        break      
if p==True:
    print("{}是素数".format(m))
else:
    print("{}不是素数".format(m))

