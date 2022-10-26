#"hh:mm:ss.09ns" 格式字符串，转为ns数    1s=10^9ns

def trans(s:str) -> int:
    s=s.split(":")
    print(s)
    s_ns = s[2].split('.')
    print(s_ns)
    ans = 0
    ans+=int(s[0])*3600*10**9
    ans+=int(s[1])*60*10**9
    ans+=int(s_ns[0])*10**9+int(s_ns[1])
    return ans


if __name__ == '__main__':
    str1 = "00:10:11.000000011"
    count1 =trans(str1)
    print(count1) 



