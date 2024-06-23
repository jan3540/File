# try:
#     x=int(input('please press x:'))
#     y=int(input('please press y:'))
#     z = x/y
#     print(z)
# except ZeroDivisionError:
#     print("y don't is 0")

# except: 如果try中内容异常，输出except后的内容
# try:
#     x=1
#     print(y)
# except:
#     print('error')


# import math
# num=0
# for a in range(1,21):
#     for b in range(a+1,21):
#         for c in range(b+1,21):
#             if math.sqrt(a**2+b**2)==c:
#                 num+=1
#                 print(a,b,c)
# print('pair is',num)


# n=20
# f1=f2=1
# print(f1,f2)
# for i in range(3,n+1):
#     f1,f2=f2,f1+f2
#     print(f2)