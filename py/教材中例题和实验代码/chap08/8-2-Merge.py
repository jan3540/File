# 例8-2
import pandas as pd
try:
    total_df = pd.read_csv('total.csv', encoding='utf-8')
except UnicodeDecodeError:
    total_df = pd.read_csv('total.csv', encoding='gbk')
try:
    class1_df = pd.read_csv('class1.csv', encoding='utf-8')
except UnicodeDecodeError:
    class1_df = pd.read_csv('class1.csv', encoding='gbk')
result_df = pd.merge(class1_df, total_df, on='学号', how='left')
result_df.to_csv('class1.csv', index=False, encoding='gbk')