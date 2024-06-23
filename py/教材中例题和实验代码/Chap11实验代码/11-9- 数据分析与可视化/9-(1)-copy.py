import numpy as np

# 创建初始数组 array_a
array_a = np.array([1, 2, 3, 4, 5])

# 将 array_a 的数值赋值给 array_b
array_b = array_a.copy()

# 修改 array_a 和 array_b 的数值
array_a *= 5  # array_a 点乘 5
array_b *= 10  # array_b 点乘 10

# 打印输出 array_a 和 array_b 的最终数值
print("array_a 的最终数值：", array_a)
print("array_b 的最终数值：", array_b)