def func1(n,c):
    n=2
    c="welcome"
    print("          形参n和c的值为:",n,c)

num=1
ch="hello"
print("调用func1前num和ch的值为:",num,ch)
func1(num,ch)       # 无返回值函数的调用，作为一条独立的语句
print("调用func1后num和ch的值为:",num,ch)
