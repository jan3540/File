class Person(object):
    "人的简单描述，属性（姓名，年龄）；方法（初始化、显示姓名、显示年龄）"
    age=0
    def __init__(self,n):
        self.name=n
    def show_name(self):
        print(self.name)
    def show_age(self):
        print(self.age)
        
zhangsan=Person("张三")
zhangsan.age=18
zhangsan.show_name()
zhangsan.show_age()
print(Person.age)
