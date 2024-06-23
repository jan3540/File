ch=input("输入需要加密的字符串：").upper()
key=int(input("输入加密的偏移量："))
abc=[chr(x) for x in range(65,91)]   # 生成26个大写字母的列表
d={}
for i in range(0,26):                # 根据偏移量，构建字母的映射字典 
    d[abc[i]]=abc[(i+key)%26]        
code=""
for c in ch:                         # 字符串加密
    if "A"<=c<="Z":
        code=code+d[c]
    else:
        code=code+c
print("加密后的字符串：",code)
