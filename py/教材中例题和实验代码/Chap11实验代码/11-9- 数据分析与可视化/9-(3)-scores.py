import pandas as pd
# 读取数据
data = pd.read_csv('stu.csv', encoding='gbk')
# 输出所有出现不及格科目的同学的信息
failed_students = data[(data['语文'] < 60) | (data['数学'] < 60) | (data['英语'] < 60)]
print("不及格科目的同学信息：")
print(failed_students)
# 统计并打印每个班级的各门课的平均分
class_avg = data.groupby('班级').agg({'语文': 'mean', '数学': 'mean', '英语': 'mean'})
# agg({'语文': 'mean', '数学': 'mean', '英语': 'mean'})：这部分代码表示对每个分组（即每个班级）进行聚合操作，其中{'语文': 'mean', '数学': 'mean', '英语': 'mean'}指定了要对哪些列进行聚合操作以及使用哪种聚合函数。在这里，我们使用mean函数计算每个班级的语文、数学、英语三门课程的平均值。
print("\n每个班级的各门课的平均分：")
print(class_avg)