from math import sqrt
num=0
print("50以内的自然数对有：")
for a in range(1,50):
    for b in range(a+1,51):
        if sqrt(a+b)==int(sqrt(a+b)) and sqrt(b-a)==int(sqrt(b-a)):
            print(a,b)
            num+=1
print("自然数对共有",num,"对。",sep='')
    
