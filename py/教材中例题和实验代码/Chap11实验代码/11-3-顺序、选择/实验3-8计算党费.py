salary=eval(input("请输入工资:"))
if salary<=400:
    f=salary*0.005
elif salary<=600:
    f=salary*0.01
elif salary<=800:
    f=salary*0.015
elif salary<=1500:
    f=salary*0.02
else:
    f=salary*0.03
print("工资{}，应缴党费{:.2f}元".format(salary,f))
      

