def some_func():
    try:
        return 'from_try'
    finally:
        return 'from_finally'
a = some_func()
print(a)
