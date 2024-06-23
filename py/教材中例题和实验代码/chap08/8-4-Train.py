import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
# 创建年份和高铁总里程的数据
years = np.arange(2008, 2023)
total_KMage = [0.0672, 0.2699, 0.5133, 0.6601, 0.9356, 1.1028, 1.6456, 1.9838, 2.2980, 2.5164, 2.9904, 3.5388, 3.7929, 4.0000, 4.2000]
# 创建Pandas数据
data = pd.DataFrame({'Year': years, 'Total KMage': total_KMage})
# 创建图表
plt.figure(figsize=(20, 6)) # 创建一个宽为20英寸高为6英寸的图像画布
plt.plot(data['Year'], data['Total KMage'], 'b-o')
# 设置x坐标和y坐标的样式
plt.xticks(data['Year'], fontsize=15) # 横坐标数据用data['Year']表示，字号为15磅
plt.yticks(fontsize=15) # 纵坐标数据字号为15磅
plt.ylim(0,4.5) # 纵坐标数据范围限定为0到4.5
# 添加标题和x坐标、y坐标的标签
plt.title('中国高铁历年营业里程（2008年-2022年）', fontproperties='SimHei', fontsize = 20) # 设置图像标题，字号为20磅，显示中文需将fontproperties设置为中文字体
plt.xlabel('年份', fontproperties='SimHei', fontsize = 20) # 设置横坐标标签，字号为20磅
plt.ylabel('营业里程 (万公里)', fontproperties='SimHei', fontsize = 20) # 设置纵坐标标签，字号为20磅
# 在折线附近标注出对应年份的具体营业里程
for i in range(len(total_KMage)):
    plt.text(data['Year'][i], data['Total KMage'][i]+0.1, str(data['Total KMage'][i]), ha='center', fontsize=12) # 在图像的(data['Year'][i], data['Total KMage'][i]+0.1)坐标处显示数据“str(data['Total KMage'][i])”，居中对齐，字号为12磅
# 添加网格线
plt.grid(True)
# 显示图表
plt.show()