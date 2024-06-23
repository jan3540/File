#砝码种类
kind = int(input())
#砝码重量
weight = (input()).strip().split(' ')
#砝码数量
number = [int(a) for a in (input()).strip().split(' ')]
list_kind = []
set_weight = {0, }
for a in range(kind):
    for i in range(number[a]):
        list_kind.append(weight[a])
for q in list_kind:
    for ww in list(set_weight):
        set_weight.add(int(q) + ww)
print(len(set_weight))
