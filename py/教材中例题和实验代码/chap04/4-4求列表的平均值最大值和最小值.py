def proc(arr): 
    s = sum(arr)
    avg = round(s/len(arr),2)
    return avg,max(arr),min(arr)
  
a=[6.6, 9.9, 9.7, 55.2, 7.3, 9.5, 12.8, 7.9, 16.0, 16.8]
m=proc(a)
print(m)
print("average={0}, max={1}, min={2}".format(m[0],m[1],m[2]))

