def match_parentheses(s):
    # 把一个list当做栈使用
    ls = []
    parentheses = "()"
    for i in range(len(s)):
        si = s[i]
        # 如果不是括号则继续
        if parentheses.find(si) == -1:
            continue
        # 左括号入栈
        if si == '(':
            ls.append(si)
            continue
        if len(ls) == 0:
            return False
        # 出栈比较是否匹配
        p = ls.pop()
        if p == '(' and si == ')':
            continue
        else:
            return False
    if len(ls) > 0:
        return False
    return True

n=input()
result = match_parentheses(n)
if result==True:
    print("配对成功")
else:
    print("配对不成功")
