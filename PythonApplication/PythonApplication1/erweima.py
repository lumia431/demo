
from MyQR import myqr

'''
words：内容
version：容错率
save_name：保存的名字
'''
myqr.run(words='https://www.baidu.com/',
         version=1,
        save_name='myqr.png')