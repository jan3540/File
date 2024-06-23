def total(**dic):
    s=0
    for i in dic.values():
        s=s+i
    print(dic)
    return s
print("总分:",total(语文=98,数学=95,英语=80))


