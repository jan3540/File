class BMI(object):
    def __init__(self,h,w):
        self.height=h
        self.weight=w
        self.BMI=w/(h**2)
    def printBMI(self):
        print("{:.1f}".format(self.BMI))
class ChinaBMI(BMI):
    def __init__(self,h,w):
        self.height=h
        self.weight=w
        self.BMI=w/(h**2)
    def printBMI(self):
        BMI.printBMI(self)
        if self.BMI<18.5:
            print("偏瘦，相关疾病发病的危险性：低")
        if 18.5<=self.BMI<=23.9:
            print("正常，相关疾病发病的危险性：平均水平")
        if 23.9<self.BMI<=26.9:
            print("偏胖，相关疾病发病的危险性：增加")
        if 26.9<self.BMI<=29.9:
            print("肥胖，相关疾病发病的危险性：中度增加")
        if self.BMI>29.9:
            print("重度肥胖，相关疾病发病的危险性：重度增加")
s1=ChinaBMI(1.8,80)
s1.printBMI()
