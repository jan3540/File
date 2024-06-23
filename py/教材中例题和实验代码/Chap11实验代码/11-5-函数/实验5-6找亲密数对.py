def mysum(a):
    s=0
    for i in range(1,a//2+1):
       if a%i==0:
           s=s+i
    return s

for A in range(1,3000):
    B=mysum(A)
    if A<B and mysum(B)==A:
        print("亲密数对: A={:4d}, B={:4d}".format(A,B))
