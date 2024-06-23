print("1000以内的全部同构数有：")
for i in range(1,1001):
    if i*i%10==i or i*i%100==i or i*i%1000==i:
        print(i)
