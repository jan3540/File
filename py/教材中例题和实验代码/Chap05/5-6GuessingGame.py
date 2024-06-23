import random
class Computer():
    def __init__(self):
        self.m = random.randint(1,3)
class Player():
    def __init__(self):
        self.m = int(input("你出什么?"))
class GuessingGame():
    def __init__(self):
        self.choicelist = ["石头","剪刀","布"]
    def gameP(self):
        gamec = Computer()
        gamep = Player()
        if gamep.m == gamec.m:
            print("你出{}，计算机也出{}，平局！"\
                  .format(self.choicelist[gamep.m-1],self.choicelist[gamec.m-1]))
        elif gamep.m - gamec.m == -1 or gamep.m - gamec.m == 2:
            print("你出{}，计算机出{}，你赢了！"\
                  .format(self.choicelist[gamep.m-1],self.choicelist[gamec.m-1]))
        else:
            print("你出{}，计算机出{}，你输了！"\
                  .format(self.choicelist[gamep.m-1],self.choicelist[gamec.m-1]))
    def playGame(self):
        while True:
            i = int(input("欢迎来猜拳!进入游戏请输入1，退出游戏请输入2："))
            if i == 1:
                print("计算机已出拳，如果你想出石头请选1，剪刀选2，布选3")
                self.gameP()
            elif i == 2:
                break
            else:
                print("数据不合法")
game1=GuessingGame()
game1.playGame()
