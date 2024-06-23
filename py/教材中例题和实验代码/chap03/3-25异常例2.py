try:
    x=int(input("请输入x:"))
    y=int(input("请输入y:"))
    z=x%y
    print("{}%{}={}".format(a,y,z))
except ZeroDivisionError:
    print("除数为0了！")
except ValueError:
    print("输入了非整数数字符号了！")
except:
    print("发生了其他异常！")
else:
    print("程序正常运行，没有发生异常!")
finally:
    print("异常演示结束，你学懂了吗？")






    

