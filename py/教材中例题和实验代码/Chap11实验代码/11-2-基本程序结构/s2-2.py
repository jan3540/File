x=0
y=True
print(x>y and 'a'<'b', 'ab'=='a'+'b', 'ab'>='ac')

x={1: '1', 2: '2', 3: '3',4: '4'}
print(len(x), type(x))

str=['abcdefg', '1234567', '我的朋友在哪里', '在北京在上海']
print(str[-1][-1], str[0][3], str[3][4])

L=[1,2,3,4,5]
L.append([6,7,8,9,10])
LN=L.pop()
print(len(L),max(LN),min(L))

t1=tuple("二月春风似剪刀")
t2=t1*2
print(sorted(t1))
print('春' in t2)
