//"hh:mm:ss.09ns" 格式字符串，转为ns数 1s=10^9ns
//注意点：
//  1.long是32位，不够大，会溢出，所以需要long long或者 unsigned long long存储答案
//  2.c中数字字符转对应数字需要用atos/atoi/atol做转换，或者用 char-‘0’ 直接获取对应单个字符的ascii码减去 ‘0’ 的ascii码也能得到 0-9对应数字
// 3.ato* 是读字符指针，一直往后读到非数字字符停止，返回 * 对应的数据类型的数字

#include <stdio.h>
#include<stdlib.h>

unsigned long long trans(char *c)
{
    unsigned long long ans = 0;
	ans +=(unsigned)(atoi(c+9));
	ans +=(unsigned long long)(atoi(c+6))*1000000000;
	ans +=(unsigned long long)(atoi(c+3))*60*1000000000;
	ans +=(unsigned long long)(atoi(c))*60*60*1000000000;

    
    return ans;
}

int main()
{
    char ch[] = {"00:00:10.000000600"};
    unsigned long long ans = trans(ch);
    printf("%llu\n", ans);
    printf("%d\n", ch[18]);
    // printf("%c\n", ch[19]);
    return 0;
}