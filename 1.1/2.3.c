#include <stdio.h>
int main()
{
    int num = 123;
    char str[10];
    sprintf(str, "%d", num);
// 现在，str的内容是"123"
    printf("%s\n",str);
printf("str: %s\n", str);


    return 0;
}
