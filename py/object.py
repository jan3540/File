# class Dog:
#     def __init__(self, name, age):
#         self.name = name  # 属性
#         self.age = age    # 属性

#     def bark(self):
#         print(f"{self.name} is barking")  # 方法

#     def get_age(self):
#         return self.age  # 方法
    
# #创建对象
# dog1 = Dog("Buddy", 3)
# dog2 = Dog("Lucy", 5)

# # 调用方法
# dog1.bark()  # 输出: Buddy is barking
# dog2.bark()  # 输出: Lucy is barking

# # 获取属性
# print(f"{dog1.name} is {dog1.get_age()} years old")  # 输出: Buddy is 3 years old
# print(f"{dog2.name} is {dog2.get_age()} years old")  # 输出: Lucy is 5 years old

# class person():
#     'person object'
#     age=0
#     def __init__(self,n):
#         self.name=n

#     def show_name(self):
#         print(self.name)

#     def show_age(self):
#         print(self.age)
        
# zhangsan=person('zs2')  
# # 实例变量=类名   用于定义zhangsan 并初始化self.name=zs

# zhangsan.age=18        
# #实例变量.属性名  18

# #上面用于初始化，下面用于实际调用输出

# zhangsan.show_name()   
# #实例变量.属性名  

# zhangsan.show_age()    
# #实例变量.属性名  

# print(person.age)      
# #默认age=0

# print(zhangsan.age)  

#只存在self
# class num(object):
#     def __init__(self,num1,num2):
#         self.num1=num1
#         self.num2=num2
        
#     def sum(self):
#         print(f'{self.num1} and {self.num2} add is {self.num1+self.num2}')

#     def jian(self):
#         print(f'{self.num1} and {self.num2} jian is {self.num1-self.num2}')
        
# s1=num(1,2)

# s1.sum()
# s1.jian()


#  #引入新参数
# class num(object):
#     def __init__(self, num1, num2):
#         self.num1 = num1
#         self.num2 = num2

#     def sum(self, extra=0):  # 方法包含 self 和额外的参数 extra，默认值为0
#         result = self.num1 + self.num2 + extra
#         print(f'{self.num1} and {self.num2} add with {extra} is {result}')

#     def jian(self, extra=0):  # 方法包含 self 和额外的参数 extra，默认值为0
#         result = self.num1 - self.num2 - extra
#         print(f'{self.num1} and {self.num2} subtract with {extra} is {result}')
        
# s1 = num(1, 2)

# s1.sum()  # 没有传递额外参数，使用默认值0
# s1.sum(3)  # 传递额外参数3
# s1.jian()  # 没有传递额外参数，使用默认值0
# s1.jian(1)  # 传递额外参数1


class accout:
    def __init__ (self,id):
        self.id=id
        id=888
        
acc=accout(100)
print(acc.id)