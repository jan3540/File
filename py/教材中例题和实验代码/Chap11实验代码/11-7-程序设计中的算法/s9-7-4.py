def twoSum(nums, target):
    for index1,i in enumerate(nums):
        for index2,j in enumerate(nums):
            if i+j == target and i != j:
                return index1,index2


a = list(map(int,input().split(',')))
b = int(input())
print(list(twoSum(a,b)))
