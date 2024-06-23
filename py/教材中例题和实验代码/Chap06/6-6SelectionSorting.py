def Selection_sort(arr):
    n = len(arr)
    for i in range(n - 1):
        min_index = i
        for j in range(i + 1, n):
            if arr[j] < arr[min_index]:
                min_index = j
        arr[min_index], arr[i] = arr[i], arr[min_index]
array = [3, 5, 9, 7, 2, 1]
print("排序前",array)
Selection_sort(array)
print("排序后",array)

