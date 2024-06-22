#抽烟问题 刚开始有n颗烟，每k颗换1颗，求共能抽到多少根烟
ch=input()
n,k=ch.split()
n=int(n)
k=int(k)
s=n
while n>=k:
    n=n-k+1
    s=s+1
print(s)
    
    
