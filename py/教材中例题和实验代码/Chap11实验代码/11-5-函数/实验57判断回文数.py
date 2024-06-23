def huiwen1(x):
    if str(x)==str(x)[::-1]:
        return True
    return False
'''
def huiwen2(x):
    y=0
    xx=x
    while x>0:
        y=y*10+x%10
        x=x//10
    if xx==y:
        return True
    else:
        return False
    
def huiwen3(x):
    ch=str(x)
    for i in range(1,len(ch)+1):
        if ch[i-1]!=ch[-i]:
            return False
    return True
'''
if __name__=='__main__':
    
    M=int(input("请输入正整数M:"))

    if huiwen1(M)==True:
        print(M,"是回文数",sep='')
    else:
        print(M,"不是回文数",sep='')
    '''    
    if huiwen2(M):
        print(M,"是回文数",sep='')
    else:
        print(M,"不是回文数",sep='')
        
    if huiwen3(M):
        print(M,"是回文数",sep='')
    else:
        print(M,"不是回文数",sep='')
    '''
