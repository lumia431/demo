
def foo():
    print("starting...")
    while True:
		#赋值没有完成就直接yield出去了
        yield 4+1
        print("res:",res)
g = foo()
print(next(g))
print("*"*20)
print(next(g))
print(g.send(7))