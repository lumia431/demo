import urllib .request  #导入用于打开URL的扩展库模块
import urllib .parse
import re    #导入正则表达式模块

def open_url(url):
  req=urllib .request .Request (url)   #将Request类实例化并传入url为初始值，然后赋值给req
  #添加header，伪装成浏览器
  req.add_header('User-Agent','Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36 SE 2.X MetaSr 1.0')
  #访问url，并将页面的二进制数据赋值给page
  page=urllib .request .urlopen(req)
  #将page中的内容转换为utf-8编码
  html=page .read().decode('utf-8')

  return html

def get_img(html):
  # [^"]+\.jpg 匹配除"以外的所有字符多次,后面跟上转义的.和png
  p=r'<img src="([^"]+\.png)"'
  #返回正则表达式在字符串中所有匹配结果的列表
  imglist=re.findall(p,html )

  #循环遍历列表的每一个值
  for each in imglist :
    #以/为分隔符，-1返回最后一个值
    filename=each.split("/")[-1]
    #访问each，并将页面的二进制数据赋值给photo
    photo=urllib .request .urlopen(each )
    w=photo .read()
    #打开指定文件，并允许写入二进制数据
    f=open('D://pics//'+filename+'.png','wb')
    #写入获取的数据
    f.write(w)
    #关闭文件
    f.close()

#该模块既可以导入到别的模块中使用，另外该模块也可自我执行
if __name__=='__main__':
  #定义url
  url="https://image.baidu.com/search/index?tn=baiduimage&ps=1&ct=201326592&lm=-1&cl=2&nc=1&ie=utf-8&dyTabStr=MCw0LDEsNiw1LDMsNyw4LDIsOQ%3D%3D&word=Python%E7%88%AC%E8%99%AB%E4%B9%8B%E7%88%AC%E5%8F%96%E7%BD%91%E7%AB%99%E5%9B%BE%E7%89%87"
  #将url作为open_url()的参数，然后将open_url()的返回值作为参数赋给get_img()
  get_img(open_url(url))