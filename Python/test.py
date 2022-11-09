# 韩信派兵 算兵数量
# def test():
#     while(1):
#         num = input()
#         if not num:
#             break
#         num = num.split()
#         flag = True
#         if len(num) == 3 and int(num[0]) < 3 and int(num[1]) < 5 and int(num[2]) < 7:
#             for i in range(10, 101):
#                 if i % 3 == int(num[0]) and i % 5 == int(num[1]) and i % 7 == int(num[2]):
#                     print(i)
#                     flag = False
#                     break
#         if not flag:
#             continue
#         print("No answer")
#         continue

# test()

# 标准输入流
import sys
for item in sys.stdin:
    t=item.split()
    print(t)
