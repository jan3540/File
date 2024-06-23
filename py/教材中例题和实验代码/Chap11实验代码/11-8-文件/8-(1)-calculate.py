# 读取数据
with open('sy8-1a.txt', 'r') as file:
    data = file.read().split(', ')
    data = [int(x) for x in data]

# 计算最大值、最小值和均值
max_value = max(data)
min_value = min(data)
average_value = sum(data) / len(data)

# 将结果写入文件
with open('sy8-1b.txt', 'w') as file:
    file.write(f'最大值: {max_value}\n')
    file.write(f'最小值: {min_value}\n')
    file.write(f'均值: {average_value}\n')