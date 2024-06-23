# a,b,c=eval(input('sig a b c:'))
# print ('a',a)
# print ('b',b)
# print ('c',c)

# a='123456'
# b='2468'
# print('a_len:',len(a))
# print('b_len:',len(b))
# print('b_len:',len(a+b))


# a='012345'
# print(a[0]+a[2]+a[1]+a[5])
# print(a[0]+a[2]+a[1]+a[5])   
# print(a[0:5:2],a[2:6:1],sep='|') #stap sep

#列表 []  元素可变
# list1=[]
# list2=list(range(1,10,1))
# list3=['1','2','3']
# print(list2)
# print(list2[0:4])
# print(list2[1:4])
# print(list2[3:4])

# list2.pop(3)   #删除索引值为3的元素
# print(list2[1:4])

# list2.append('jjt')  #末尾添加"jjt"
# print(list2[1:8])
# print(list2[1:9])

# list2.remove(2)   #删除指定元素2，存在多个只删除第一个
# print(list2[1:8])
# list4=['a','b','d','c']

# list4.sort()  #顺序排序，修改元素
# print(list4)

# list4.reverse()  #逆序排序，修改元素
# print(list4)

#元组()  元素不可变
# a=(1,2,3,4,5)
# print(a)
# print(min(a),max(a))
# print(sorted(a))  #顺序排序，不修改元素

#集合{}  元素可变，唯一，无序
# s1=set()
# s2={0,1,2,3,4,5,5,4,3}
# s3={"hello"}
# s3=frozenset("hello")

# s2.add(6)  #添加元素6
# print(s2)

# s2.discard(6)  #删除元素6
# print(s2)

# s2.discard(7)
#  print(s1)
# print(s2)
# print(s3)

# s2.copy()  #返回副本
# print(s2)

# s2.clear()  #清除所有元素
# print(s2)

#字典{a:b}   a键：b值   键值对，无序对象集合
# s1={}
# s2={'jjt1':'1.com',"jjt2":'2.com','jjt3':'3.com'}
# print(s2)  
#运行结果随机排序
# print(s2['jjt1'])
# print(s2['jjt2'])
# print(s2['jjt3'])
# print('len_s2:',len(s2))
# print(s2.keys())
# print(s2.values())
# s2['jjt4']='4.com'  #添加键值对
# print(s2)
# s2['jjt4']='new_4.com' #修改键值对
# print(s2)
# print(s2.items())  #返回键值对所构成的列表
# print(sorted(s2.items()))  #排序
