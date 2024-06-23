import csv
import random

# 生成20个0到100之间的随机数
random_numbers = [random.randint(0, 100) for _ in range(20)]

# 将这些数写入CSV文件，每行5个数
with open('sy8-4.csv', 'w', newline='', encoding='utf-8') as file:
    writer = csv.writer(file)
    for i in range(0, len(random_numbers), 5):
        writer.writerow(random_numbers[i:i+5])

print("随机数已写入sy8-4.csv文件。")