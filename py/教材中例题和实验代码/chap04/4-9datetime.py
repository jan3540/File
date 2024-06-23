from datetime import datetime
start=datetime.now()           # 获取程序运行的开始时间
for i in range(100):
   for j in range(100):
      for k in range(10000):
         pass
end=datetime.now()             # 获取程序运行的结束时间 
x=end-start                    # x是两个时间对象的差值，是datetime.timedelta类的对象
#print(x)
print(x.seconds)               # sceonds是timedelta对象的属性
#print(x.total_seconds())       # total_seconds()是timedelta对象的方法
