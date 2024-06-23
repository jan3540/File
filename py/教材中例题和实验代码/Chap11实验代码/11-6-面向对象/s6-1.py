class BMI(object):
    def __init__(self,h,w):
        self.height=h
        self.weight=w
        self.BMI=w/(h**2)
    def printBMI(self):
        print("{:.1f}".format(self.BMI))
s1=BMI(1.8,80)
s1.printBMI()
