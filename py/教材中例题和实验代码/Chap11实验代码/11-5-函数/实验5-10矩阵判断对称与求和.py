import random
def isSymmetrical(lst):
    '''文档字符串'''
    for i in range(3):
        for j in range(i+1,4):
            if lst[i][j]!=lst[j][i]:
                return False
    return True

def matrix_sum(lst):
    s=0
    for i in range(4):
        s=s+lst[i][i]
    return s
        
if __name__=="__main__":
    print("4阶矩阵：")
    lst=[]
    for i in range(4):
        ls=[]
        for j in range(4):
            ls.append(random.randint(10,99))
        lst.append(ls)
        
    for i in range(4):
        for j in range(4):
            print(lst[i][j],end=' ')
        print()
        
    if isSymmetrical(lst):
        print("矩阵是对称矩阵")
    else:
        print("矩阵不是对称矩阵")
    
    print("矩阵对角线元素和是:",matrix_sum(lst))
    
