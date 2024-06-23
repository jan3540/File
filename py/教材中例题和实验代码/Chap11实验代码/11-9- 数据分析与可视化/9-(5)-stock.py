# 9-(5)-stock
import pandas as pd
import matplotlib.pyplot as plt

# 加载数据
df = pd.read_csv('stock_prices.csv')

# 转换日期并设置索引
df['Date'] = pd.to_datetime(df['Date'])
df.set_index('Date', inplace=True)


# 绘制图表
plt.figure(figsize=(10, 5))
plt.plot(df['Price'])#, label='Close Price'
plt.title('股票价格趋势（2022年1月-2023年1月）', fontproperties='SimHei', fontsize = 16)
plt.xlabel('日期', fontproperties='SimHei', fontsize = 16)
plt.ylabel('价格', fontproperties='SimHei', fontsize = 16)
plt.legend()
plt.show()