st,k=input().split()
st=list(st)    #字符串是不可变类型，所以需要将其转化为可变类型的列表
k=int(k)    #k为密钥
for i in range(len(st)):
    if 96<ord(st[i])<123:
        st[i]=chr((ord(st[i])-97+k)%26+97)
    if 64<ord(st[i])<91:
        st[i]=chr((ord(st[i])-65+k)%26+65)
st=''.join(st)
print(st)#输出加密结果
