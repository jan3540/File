clist=[4,7,8,1,2,2,6,2,2,1,6,8,7,4,5,5,5,8,5,5,4,2,2,6,4]
c=set(clist)
print("获得选票的候选人编号:",c)
a=input("请输入候选人编号:")
print(a in str(clist))
