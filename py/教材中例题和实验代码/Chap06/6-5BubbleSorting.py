def Bubble_sort(arr):
    if len(arr) <= 1:
        return
    i = 0
    while i < len(arr):
        j = 0
        while j < len(arr)-1-i:
            if arr[j] > arr[j+1]:
                temp = arr[j+1]
                arr[j+1] = arr[j]
                arr[j] = temp
            j += 1
        i += 1

arr = [3,5,9,7,2,1]
print("排序前：",arr)
Bubble_sort(arr)
print("排序后：",arr)
