import requests
url = 'https://www.huawei.com/cn/corporate-information'
headers = {'user-agent':'Chrome/5.0'}
proxies = {'http': None, 'https': None}
try:
    Response = requests.get(url, headers = headers, proxies = proxies)
    if  Response.status_code == requests.codes.ok:
        Response.encoding = Response.apparent_encoding
        with open(r'ResponseText.txt', 'w', encoding = 'utf-8') as file:
            file.write(Response.text)
    else:
        print('该网页不允许爬取')
except IOError as Error:
    print(str(Error))