def getSumofSquares(num): #快乐数判断
    numStr=str(num)
    sum=0
    for i in numStr:
        sum += int(i)**2
    return sum


n = input() 
sumofSqrs = eval(n)
while sumofSqrs != 1 and sumofSqrs != 4: 
    sumofSqrs = getSumofSquares(sumofSqrs)
else:
    if sumofSqrs == 1:
        print("True")
    else:
        print("False")
