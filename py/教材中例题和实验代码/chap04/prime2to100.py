def prime(m):
    if m == 1:
        return False
    else:
        for i in range(2,m):
            if m % i == 0:
                return False
        return True
    
num=0
for m in range(2,101):
        if prime(m)==True:
            print(m,end=',')
            num=num+1
            if num % 10==0:
                print()     
print()
