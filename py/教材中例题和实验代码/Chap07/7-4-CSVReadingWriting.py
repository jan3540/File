# 7-4 CSVReadingWriting.py
import csv
with open(r'scores.txt', 'r', encoding='utf-8') as scores_file, open(r'scores.csv', 'w', newline='') as scores_csv_file:
    scores_csv_read = csv.reader(scores_file)
    print('调用csv.reader()函数，读取的数据类型是：'+str(type(scores_csv_read)))
    scores_csv_read = list(scores_csv_read)
    print('调用csv.reader()函数，读取的数据内容是：'+str(scores_csv_read))
    scores_csv_writerow = csv.writer(scores_csv_file)
    print('调用csv.writer()函数，写入的数据类型是：'+str(type(scores_csv_writerow)))
    for row in scores_csv_read:
        scores_csv_writerow.writerow(row)