def string_num(ch):
    n1=n2=n3=n4=0
    for c in ch:
        if c.isalpha():       #'A'<=c<='Z' or 'a'<=c<='z':
            n1=n1+1
        elif c.isdigit():     #'0'<=c<='9':
            n2=n2+1
        elif c.isspace():     #c==' ':
            n3=n3+1
        else:
            n4=n4+1
    return n1,n2,n3,n4

ch=input("请输入需要统计的字符串:")
a,b,c,d=string_num(ch)
print("统计结果：字母有{}个，数字有{}个，空格有{}个，其他字符有{}个。".format(a,b,c,d))
            
