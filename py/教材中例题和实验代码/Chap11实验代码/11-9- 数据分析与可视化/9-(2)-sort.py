import pandas as pd
data = {'姓名': ['张伟', '王丽', '李婷', '刘洋', '陈磊', '杨帆', '黄敏', '赵峰', '吴燕'],
        '成绩': [82, 93, 75, 85, 90, 88, 92, 87, 91]}
df = pd.DataFrame(data)
# print("原始数据：")
# print(df)

# 对成绩进行逆序排序并打印输出
sorted_df = df.sort_values(by='成绩', ascending=False)
print("\n逆序排序后的数据：")
print(sorted_df)
