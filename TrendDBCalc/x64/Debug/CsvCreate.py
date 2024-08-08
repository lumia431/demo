
def run(dataStr,path):
    with open(path, 'w', newline='') as cf:
        cf.writelines(dataStr)
 