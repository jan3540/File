class Vehicle():
    def __init__(self,speed,size,time,acceleration):
        self.speed = speed
        self.size = size
        self.time = time
        self.acceleration = acceleration
    def move(self):
        return "初速度:{} 加速度:{} 体积:{}".format(self.speed,self.acceleration,self.size)
    def setspeed(self):
       return "设置的初速度为:{}".format(self.speed)
    def speedUp(self):
        speed_end_up = self.speed + self.acceleration*self.time
        return "加速完后速度是:{}".format(speed_end_up)
    def speedDown(self):
        speed_end_down = self.speed - self.acceleration*self.time
        if speed_end_down < 0:
            return"减速完后速度是:0"
        else:
            return "减速完后速度是:{}".format(speed_end_down)
car = Vehicle(1,2,5,2)
print(car.move())
print(car.setspeed())
print(car.speedUp())
print(car.speedDown())
