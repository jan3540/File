import requests
import jieba
url = 'https://baike.baidu.com/item/Python/407313?fr=ge_ala'
headers = {'user-agent':'Chrome/5.0'}
proxies = {'http': None, 'https': None}
try:
    Response = requests.get(url, headers = headers, proxies = proxies)
    if  Response.status_code == requests.codes.ok:
        Response.encoding = Response.apparent_encoding
        # print(Response.text)
        # with open(r'ResponseText.txt', 'w', encoding = 'utf-8') as file:
        #     file.write(Response.text)
        words=jieba.lcut(Response.text, cut_all=False)
        words_freq = {}
        # print(words[:10])
        for chars in words:
            # if len(chars) < 2:
            #     continue
            if chars in words_freq:
                words_freq[chars] += 1
            else:
                words_freq[chars] = 1    
        # 按照字频降序排序
        # words_freq_sorted = sorted(words_freq.items(), key=lambda x: x[1], reverse=True)
        words_freq_sorted = sorted(words_freq.items(), key=lambda x: x[1], reverse=True)
        print(words_freq_sorted[:5])
    else:
        print('该网页不允许爬取')
except IOError as Error:
    print(str(Error))