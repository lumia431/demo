# bs4_tencent.py


from bs4 import BeautifulSoup
import urllib.request
import urllib
import json    # 使用了json格式存储

def tencent():
    #url = 'http://hr.tencent.com/'
    #request = urllib.request.Request(url + 'position.php?&start=10#a')
    #response =urllib.request.urlopen(request)
    #resHtml = response.read()

    #output =open('tencent.json','wb')

    #html = BeautifulSoup(resHtml,'lxml')

    url = 'http://117.50.192.150/'
    request = urllib.request.Request(url)
    res = urllib.request.urlopen(request)
    soup = BeautifulSoup(res,"html.parser")
    book_div = soup.find(attrs={"id":"body-wrap"})
    print(book_div)


if __name__ == "__main__":
   tencent()
