#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;

int main()
{
    FILE *fp = NULL;
    fp = fopen("date/tmp.txt", "w+");
    printf("%p\n", fp);
    fprintf(fp, "helloworld");
    fclose(fp);
    system("pause");
    return 0;
}