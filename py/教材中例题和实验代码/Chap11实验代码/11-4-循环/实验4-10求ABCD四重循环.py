for A in range(1,10):
    for B in range(0,10):
        for C in range(0,10):
            for D in range(0,10):
                x=A*1000+B*100+C*10+D
                y=C*100+D*10+C
                z=A*100+B*10+C
                if x-y==z:
                    print("A={}, B={}, C={}, D={}".format(A,B,C,D))
