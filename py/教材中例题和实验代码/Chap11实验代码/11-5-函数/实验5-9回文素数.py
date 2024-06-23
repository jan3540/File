import 实验57判断回文数 as h
import 实验58哥德巴赫猜想 as g
c=0
num=2
print("前100个回文素数分别是:")
while c<100:
    if h.huiwen1(str(num)) and g.prime(num):
        c=c+1
        print(num,end=',')
        if c % 10 ==0:
            print()
    num=num+1
    
'''def huiwen(ch):
    if ch==ch[::-1]:
        return True
    return False

def prime(m):
    for i in range(2,m):
        if m % i == 0:
            return False
    return True
   
c=0
num=2
while c<100:
    if huiwen(str(num)) and prime(num):
        c=c+1
        print(num,end=',')
        if c % 10 ==0:
            print()
    num=num+1
'''
