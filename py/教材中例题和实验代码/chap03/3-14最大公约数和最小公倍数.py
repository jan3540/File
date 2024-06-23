m,n=eval(input("请输入正整数m和n："))
for i in range(min(m,n),0,-1):
    if m % i == 0 and n % i == 0:
        gcd=i
        break
for i in range(max(m,n),m*n+1):
    if i % m == 0 and i % n == 0:
        lcm=i
        break
print("{}和{}的最大公约数是{}，最小公倍数是{}。".format(m,n,gcd,lcm))
