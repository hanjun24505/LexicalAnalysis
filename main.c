#include "LexicalAnalysis.h"

char Scanin[300],Scanout[300];
extern int TESTscan();
FILE *fin,*fout;//ָ����������ļ���ָ��
int main()
{
    int i;
    char ch;
    int es=0;
    for(i=0;i<4;i++)
    {
        es=TESTscan();
        if(es>0)
            printf("�ʷ������д���\n");
        else
            printf("�ʷ������ɹ���\n");
        printf("-------------------------------------------------------------------------\n");
        printf("\n");
        printf("\n");
    }

}










