'''
只输出求到的完数 6 28 496
for i in range(1,1001):
    s=0
    for j in range(1,i//2+1):
        if i % j == 0:
            s=s+j
    if i==s:
        print(i,end=' ')
'''
# 输出6=1+2+3的形式
print("求出的完数有：")
for i in range(1,1001):
    lst=[]
    for j in range(1,i//2+1):
        if i % j == 0:
            lst.append(j)
    s=sum(lst)
    if i==s:
        lst1=map(str,lst)
        print(s,'=',"+".join(lst1),sep='')
