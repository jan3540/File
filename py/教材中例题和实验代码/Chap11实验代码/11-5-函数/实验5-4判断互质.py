import random
def coprime(a,b):
    while a%b!=0:
        r=a%b
        a=b
        b=r
    if b==1:
        return True
    else:
        return False

a=random.randint(1,99)
b=random.randint(1,99)
print("产生的随机数是:",a,b)
if coprime(a,b)==True:
    print("{}和{}互质".format(a,b))
else:
    print("{}和{}不互质".format(a,b))
