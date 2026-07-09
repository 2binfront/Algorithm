#include <stdio.h>
#include <string.h>

#define MAXLEN 1000

// 求 nextval 数组
void GetNextVal(const char *pattern, int nextval[])
{
    int i = 0;
    int j = -1;

    nextval[0] = -1;

    while (pattern[i] != '\0')
    {
        if (j == -1 || pattern[i] == pattern[j])
        {
            i++;
            j++;

            if (pattern[i] == pattern[j])
                nextval[i] = nextval[j];
            else
                nextval[i] = j;
        }
        else
        {
            j = nextval[j];
        }
    }
}

// 返回第一次匹配的位置，失败返回-1
int KMP(const char *text, const char *pattern)
{
    int nextval[MAXLEN];

    GetNextVal(pattern, nextval);

    int i = 0;
    int j = 0;

    while (text[i] != '\0' && pattern[j] != '\0')
    {
        if (j == -1 || text[i] == pattern[j])
        {
            i++;
            j++;
        }
        else
        {
            j = nextval[j];
        }
    }

    if (pattern[j] == '\0')
        return i - j;

    return -1;
}

int main()
{
    char text[MAXLEN] = "ababcabcacbab";
    char pattern[MAXLEN] = "abcac";

    int pos = KMP(text, pattern);

    printf("%d\n", pos);

    return 0;
}
