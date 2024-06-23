def func2(lstA):
    print("调用中形参列表的值为:{}，id值为:{}。".format(lstA,id(lstA)))
    lstA=[10,20,30]
    print("赋值后形参列表的值为:{}，id值为:{}。".format(lstA,id(lstA)))
    
lst=[1,2,3]
print("调用前实参列表的值为:{}，id值为:{}。".format(lst,id(lst)))
func2(lst)  
print("调用后实参列表的值为:{}，id值为:{}。".format(lst,id(lst)))

