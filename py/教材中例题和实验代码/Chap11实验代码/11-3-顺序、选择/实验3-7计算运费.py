w=eval(input("请输入托运行李的重量(kg):"))
if w<=50:
    y=w*0.25
else:
    y=50*0.25+(w-50)*0.35
print("行李托运的运费是:",y,"元",sep="")
