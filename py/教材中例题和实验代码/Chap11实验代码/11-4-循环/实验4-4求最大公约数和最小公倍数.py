import random
a=random.randint(10,99)
b=random.randint(10,99)
c=random.randint(10,99)
print("产生的三个随机整数分别是:",a,b,c)
for i in range(min(a,b,c),0,-1):
    if a % i == 0 and b % i == 0 and c % i == 0:
        gcd=i
        break
for i in range(max(a,b,c),a*b*c+1):
    if i % a == 0 and i % b == 0 and i % c == 0:
        lcm=i
        break
print("{}、{}和{}的最大公约数是{}，最小公倍数是{}。".format(a,b,c,gcd,lcm))
