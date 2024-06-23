def fun1(n):    # 递推法
    s=0
    for i in range(1,n+1):
        s=s+i/(2*i+1)
    return s

def fun2(n):    # 递归法
    if n==0:
        return 0
    else:
        return n/(2*n+1)+fun2(n-1)

if __name__=="__main__":
    n=int(input("请输入级数的项数n："))
    print("递推法 f({})= {}".format(n,fun1(n)))
    print("递归法 f({})= {}".format(n,fun2(n)))
