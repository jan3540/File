class Circle(object):
    "圆的简单描述：半径；初始化、计算圆周长、计算圆面积、显示信息"
    def __init__(self,r):
        self.radius=r
    def get_Perimeter(self):
        return 3.14*2*self.radius
    def get_Area(self):
        return 3.14*self.radius*self.radius
    def show(self):
        print("This circle has a radius of {}.".format(self.radius))
c1=Circle(2)
print(c1.__class__.__doc__)
print(c1.get_Perimeter())
c1.show()
