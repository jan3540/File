def prime(m):
    for i in range(2,m):
        if m%i==0:
            return False
    return True

if __name__=='__main__':
    for even in range(6,51,2):
        for x in range(2,even//2+1):
            y=even-x
            if prime(x) and prime(y):
                print("{}={}+{}".format(even,x,y))
                break
