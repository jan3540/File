for a in range(1,21):
    for b in range(1,34):
        c=100-a-b
        if 5*a+3*b+c/3==100:
            print("公鸡:{:2d}只,母鸡:{:2d}只,小鸡:{:2d}只".format(a,b,c))
