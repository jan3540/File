for i in range(1000,10000):
     a = i // 1000
     b = i // 100 % 10
     c = i // 10 % 10
     d = i % 10
     cdc =c * 100 + d * 10 +c
     abc = a * 100 +b * 10 + c
     if(i-cdc == abc):
         print("A={}, B={}, C={}, D={}".format(a,b,d,d))
                    
