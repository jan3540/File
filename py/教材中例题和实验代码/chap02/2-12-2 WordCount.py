s1=input("please input a string:")
s2=input("please input a word:")
snew=s1.lower()
snew=snew.replace(","," ")
snew=snew.replace("."," ")
num=snew.count(s2)
print(num)



