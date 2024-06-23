# 9-(4)-plot
import numpy as np
import matplotlib.pyplot as plt

# 创建一个从 -10 到 10 的等差数列，包含 100 个点
x = np.linspace(-10, 10, 100)

# 计算线性函数 y = 2x + 1
y_linear = 2 * x + 1

# 计算平方函数 y = x^2
y_square = x ** 2

# 绘制线性函数，使用蓝色实线
plt.plot(x, y_linear, label='$f_1(x)=2x+1$', color='blue', linestyle='-', linewidth=2)

# 绘制平方函数，使用红色虚线
plt.plot(x, y_square, label='$f_2(x)=x^2$', color='red', linestyle='--', linewidth=2)

# 添加图例
plt.legend()

# 显示网格
plt.grid(True)

# 显示图表
plt.show()