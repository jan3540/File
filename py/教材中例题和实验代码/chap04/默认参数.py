def add(a,b,c,s=100):
    total=a+b+c+s
    return total

print(add(1,2,3))        # 位置参数，使用默认参数值
print(add(1,2,3,s=4))    # 位置参数，默认参数值被修改
print(add(c=3,b=2,a=1))  # 关键字参数，使用默认参数值
print(add(1,c=3,b=2))    # 位置参数在前，关键字参数在后，否则出错
