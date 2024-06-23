class Circle(object):
    "圆的简单描述：半径；初始化、计算圆周长、计算圆面积"
    def __init__(self,r):
        self.radius=r
    def get_Perimeter(self):
        return 3.14*2*self.radius
    def get_Area(self):
        return 3.14*self.radius*self.radius
    def show(self):
        print("This circle has a radius of {}.".format(self.radius))
class ColoredCircle(Circle):
    def __init__(self,r,c):
        Circle.__init__(self,r)
        self.color=c
    def show(self):
        Circle.show(self)
        print("It's a {} circle.".format(self.color))
cc1=ColoredCircle(4,"red")
cc1.show()
    
