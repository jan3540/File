# #最大公约数
# num1=int(input('pless press a num1:'))
# num2=int(input('pless press a num2:'))
# num3=num1 * num2
# if num1 < num2:
#     num1,num2=num2,num1
    
# yu=num1 % num2

# while yu != 0:
#     num1 = num2
#     num2 = yu
#     yu = num1 % num2
# print('yue is:',num2)
    
# #最小公倍数
# bei =num3 // num2  #最小公倍数=两数相乘//最大公约数 
# #//用于取整，/会保留小数
# print('bei is:',bei)


num1,num2=eval(input('please press num1 and num2:'))
for i in range(min(num1,num2),0,-1):
    if num1 % i ==0 and num2 % i == 0:
        yue=i
        break
    
# print(f'{num1} and {num2} yue and bei is {i} and {num1*num2//i}')
#直接通过//最大公约数求最小公倍数

for i in range(max(num1,num2),num1*num2):
    if i % num1 ==0 and i % num2 ==0:
        bei=i
        break
print(f'{num1} and {num2} yue and bei is {yue} and {bei}')