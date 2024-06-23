import matplotlib.pyplot as plt
import numpy as np
# 创建数据
x = np.linspace(0, 2*np.pi, 100)
y1 = np.sin(x)
y2 = np.cos(x)
y3 = np.tan(x)
y4 = np.exp(x)
# 创建图像窗口和子图
fig, axes = plt.subplots(nrows=2, ncols=2, figsize=(10, 8))
# 在第一个子图中绘制正弦曲线
axes[0, 0].plot(x, y1, 'b')
axes[0, 0].set_title('Sine')
# 在第二个子图中绘制余弦曲线
axes[0, 1].plot(x, y2, 'r')
axes[0, 1].set_title('Cosine')
# 在第三个子图中绘制正切曲线
axes[1, 0].plot(x, y3, 'g')
axes[1, 0].set_title('Tangent')
# 在第四个子图中绘制指数曲线
axes[1, 1].plot(x, y4, 'k')
axes[1, 1].set_title('Exponential')
# 显示图像
plt.show()