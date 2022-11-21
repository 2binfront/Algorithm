# 识别字符串是否为合法变量名
# 首字符必须为 "_" or 字母，其余字符为"_" or 字母 or 数字

import re


def identifier(str):
    template = r"^[_A-Za-z][_a-zA-Z0-9].$"
    if re.match(template, str):
        print("right")
    elif str[0] != "_" and not str[0].isalpha():
        print("first wrong")
    else:
        print("other wrong")


test1 = "11"
test2 = "abuac"
test3 = "Ab11_"
test4 = "_ "
identifier(test1)
identifier(test2)
identifier(test3)
identifier(test4)
