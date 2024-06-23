num=0
for a in range(1,21):
    for b in range(a+1,21):
        for c in range(b+1,21):
            if a*a+b*b==c*c:
                num=num+1
                print("{:2d}  {:2d}  {:2d}".format(a,b,c))
print(" 共计：",num,"对",sep="")
