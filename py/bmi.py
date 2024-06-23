weight=eval(input('weight(kg):'))
# weight=float(input('weight(kg):'))
height=eval(input('height(m):'))
# height=float(input('height(m):'))
bmi=weight/height**2
print('bmi is:',bmi)
if bmi < 18.5:
    print('thin')
elif 18.5<=bmi<23.0:
    print('good')
elif 23.0<=bmi<25.0:
    print('little fat')
elif 25.0<=bmi<30.0:
    print('so fat')
else:
    print('so so fat')
    