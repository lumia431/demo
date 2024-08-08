from enum import Enum, unique

import random


@unique
class Suite(Enum):
    """花色"""

    SPADE, HEART, CLUB, DIAMOND = range(4)
    #富比较方法
    def __lt__(self, other):
        return self.value < other.value

class Card():
    """牌"""

    def __init__(self, suite, face):
        """初始化方法"""
        self.suite = suite
        self.face = face

    def show(self):
        """显示牌面"""
        suites = ['♠︎', '♥︎', '♣︎', '♦︎']
        faces = ['', 'A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K']
        return f'{suites[self.suite.value]}{faces[self.face]}'
    #可以用于直接打印该对象
    def __repr__(self):
        return self.show()

def main():
    """主函数"""
    #构造函数里面的suite,face只是序号
    a = [Card(suite, face)
         for suite in Suite
         for face in range(1, 14)]
    print(a)


if __name__ == '__main__':
    main()