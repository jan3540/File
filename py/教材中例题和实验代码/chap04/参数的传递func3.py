def func3(lstB):
    print("调用中形参列表的值为: {}，id值为:{}。".format(lstB,id(lstB)))
    lstB[2]=30
    print("赋值后形参列表的值为:{}，id值为:{}。".format(lstB,id(lstB)))

lst=[1,2,3]
print("调用前实参列表的值为: {}，id值为:{}。".format(lst,id(lst)))
func3(lst)  
print("调用后实参列表的值为:{}，id值为:{}。".format(lst,id(lst)))
