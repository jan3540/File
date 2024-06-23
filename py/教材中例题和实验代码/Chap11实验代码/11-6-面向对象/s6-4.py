class Point():
    def __init__(self,x,y):
        self.x = x
        self.y = y
    def distance(self,other):
        lens=((self.x - other.x)**2 + (self.y - other.y)**2)**0.5
        return "{:.2f}".format(lens)
class Line():
    def __init__(self,start,end):
        self.start = start
        self.end = end
        if start.x-end.x!=0:
            self.k=(start.y-end.y)/(start.x-end.x)
        else:
            self.k=float("inf")
    def relationship(self,other):
        print(self.k,other.k)
        if self.k==other.k:
            print("平行")
        else:
            print("相交")
p1=Point(2,3)
p2=Point(4,3)
print(p1.distance(p2))
p3=Point(8,9)
p4=Point(10,9)

line1=Line(p1,p2)
line2=Line(p3,p4)
line1.relationship(line2)
