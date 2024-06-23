class Person(object):
    def __init__(self,n,a):
        self.name=n
        self.age=a
    def show(self):
        print("我的名字是{}，今年{}岁".format(self.name,self.age))
class Student(Person):
    def __init__(self,n,a,h):
        Person.__init__(self,n,a)
        self.hobby=h
s1=Student("李小龙",20,"武术")
s1.show()
