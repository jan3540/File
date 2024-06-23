# 8-(6)-lyric
import jieba
with open('歌唱祖国.txt',encoding='UTF-8') as f:
    content = f.read()
    Words=jieba.lcut(content)
    Words_freq = {}
    for chars in Words:
        if len(chars) < 2: # 不统计标点符号、换行符、单个字
            continue
        if chars in Words_freq:
            Words_freq[chars] += 1
        else:
            Words_freq[chars] = 1 # 按照字频降序排序           
        Words_freq_sorted = sorted(Words_freq.items(), key=lambda x: x[1], reverse=True)
print(Words_freq_sorted[:5])