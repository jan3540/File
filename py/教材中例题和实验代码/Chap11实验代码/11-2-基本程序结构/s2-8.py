lst = ['J0806',' J0723',' B0605',' S0901',' Z0403',' A1010']
s='J0806,J0723,B0605,S0901,Z0403,A1010'
num1 = len(lst)
print(num1)
num2 = s.count(',') + 1
num3 = len(s.split(','))
print(num2, num3)
