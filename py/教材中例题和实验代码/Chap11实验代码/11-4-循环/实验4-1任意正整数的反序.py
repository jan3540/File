x=int(input("请输入一个正整数:"))
y=0
print(x,"的反序数是:",sep='',end="")
while x>0:
    y=y*10+x%10
    x=x//10
print(y)

