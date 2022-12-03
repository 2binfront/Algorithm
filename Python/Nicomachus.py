# 给定整数，输出起始奇数最小的 尼科梅彻斯(Nicomachus)定理数列


def Nicomachus(n):
    """
    i为连串奇数起点，j为终点
    """
    target = n ** 3
    i = 1

    # # 循环次数
    # clock = 0

    # 外层循环终止
    while i < target:
        j = i
        # 通项
        sumtemp = (i + j) * ((j - i) / 2 + 1) / 2
        while sumtemp < target:
            j += 2
            sumtemp = (i + j) * ((j - i) / 2 + 1) / 2
            # clock += 1
        if sumtemp == target:
            return i, j
            # return [i, j, clock]
        i += 2
        # clock += 1


if __name__ == "__main__":
    test1 = 4
    test2 = 5
    test3 = 6
    anslist1 = Nicomachus(test1)
    anslist2 = Nicomachus(test2)
    anslist3 = Nicomachus(test3)
    # 打印起点i和末尾j
    print(anslist1, anslist2, anslist3)

