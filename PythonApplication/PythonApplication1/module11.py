import heapq
import random
#import operator
list1 = [34, 25, 12, 99, 87, 63, 58, 78, 88, 92]
list2 = [
    {'name': 'IBM', 'shares': 100, 'price': 91.1},
    {'name': 'AAPL', 'shares': 50, 'price': 543.22},
    {'name': 'FB', 'shares': 200, 'price': 21.09},
    {'name': 'HPQ', 'shares': 35, 'price': 31.75},
    {'name': 'YHOO', 'shares': 45, 'price': 16.35},
    {'name': 'ACME', 'shares': 75, 'price': 115.65}
]
list11 = sorted(list1,reverse = True)
#random.shuffle(list2)

x = {'c':'a', 'b':4, 'z':6}
ind = 88
if(ind in list1):
    print("hah")

sorted(x.items(), key=lambda d: d[1])
#字典调用sorted方法要有个新的变量接收
y = sorted(list2,key=lambda keys: keys['price'])

print(y)
#sorted_x = sorted(x.items(), key=operator.itemgetter(0))
#y=dict(sorted_x)
#print(y)
#for key,value in y.items():
#    print(key,value)

print(heapq.nlargest(3, list1))
print(heapq.nsmallest(3, list1))
print(heapq.nlargest(2, list2, key=lambda x: x['price']))
print(heapq.nlargest(2, list2, key=lambda x: x['shares']))
