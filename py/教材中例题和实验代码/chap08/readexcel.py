import pandas as pd
df = pd.read_excel(r'D:\Python\PPT-2024\chap08\score.xlsx')
print(df)
df.to_excel('f:\\score1.xlsx', sheet_name = 'score')
