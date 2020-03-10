#include "LexicalAnalysis.h"

char Scanin[300],Scanout[300];
extern int TESTscan();
FILE *fin,*fout;//指向输入输出文件的指针
int main()
{
    int i;
    char ch;
    int es=0;
    for(i=0;i<4;i++)
    {
        es=TESTscan();
        if(es>0)
            printf("词法分析有错误！\n");
        else
            printf("词法分析成功！\n");
        printf("-------------------------------------------------------------------------\n");
        printf("\n");
        printf("\n");
    }

}










