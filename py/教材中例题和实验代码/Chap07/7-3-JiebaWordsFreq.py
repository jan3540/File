#例7-3 JiebaWordsFreq.py#
import jieba
with open('二十大报告.txt',encoding='UTF-8') as file:
    content = file.read()
    words=jieba.lcut(content)
    words_freq = {}
    for chars in words:
        if len(chars) < 2:
            continue
        if chars in words_freq:
            words_freq[chars] += 1
        else:
            words_freq[chars] = 1    
    # 按照字频降序排序
    words_freq_sorted = sorted(words_freq.items(), key=lambda x: x[1], reverse=True)
    print(words_freq_sorted[:5])