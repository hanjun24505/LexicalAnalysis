#include "LexicalAnalysis.h"

char *keyword[keywordSum]={"auto","break","call","case","char","const","continue","default","do","double","else","enum","extern",
"float","for","function","goto","if","int","long","read","register","return","short","signed","sizeof","static",
"struct","switch","typedef","union","unsigned","void","volatile","while","write"};
//���嵥�ֽ��
char singleword[50]="+-*\(){}[];'\"',:.'%^";
//����˫�ֽ��
char doubleword[10]="><=!&|";

extern char Scanin[300],Scanout[300];
extern FILE *fin,*fout;//ָ����������ļ���ָ��

int TESTscan()
{
    char ch,token[40],*t;//chΪÿ�ζ�����ַ���token���ڱ���ʶ����ĵ���
    int es=0,j,n;
    printf("-------------------------------------------------------------------------\n");
    printf("������Դ�����ļ�����(test1.txt test2.txt test3.txt):");
    scanf("%s",Scanin);
    printf("-------------------------------------------------------------------------\n");
    printf("������ʷ���������ļ�����(out1.txt out2.txt out3.txt):");
    scanf("%s",Scanout);
    printf("-------------------------------------------------------------------------\n");
    if((fin=fopen(Scanin,"r"))==NULL)
    {
        printf("��Դ�����ļ�����\n");
        return 1;
    }
    if((fout=fopen(Scanout,"w"))==NULL)
    {
        printf("\n�򿪴ʷ���������ļ�����\n");
        return 2;
    }
    ch=getc(fin);//ȡһ���ַ�
    while(ch!=EOF)//û�е��ļ���β
    {
        while(ch==' '||ch=='\n'||ch=='\t') //����ǿո񣬻��У���ֱ������
            ch=getc(fin);
        if(isalpha(ch)||ch=='_')//���ch����ĸ,����б�ʶ������
        {
           token[0]=ch;
           j=1;
           ch=getc(fin);
           while(isalnum(ch)||ch=='_') //�������ĸ����
           {
               token[j++]=ch;
               ch=getc(fin);
           }
            token[j]='\0';//��ʶ����Ͻ���
            //��ؼ���
            /*
            n=0;
            while((n<keywordSum)&&strcmp(token,keyword[n]))//????????????
                n++;
            if(n>=keywordSum)
                fprintf(fout,"%s\t%s\n","ID",token);
            else
                fprintf(fout,"%s\t%s\n",token,token);
            */
            /*
            int i,j;
            for (i=0;i<keywordSum-1;i++)
            {
                for(j=i+1;j<keywordSum;j++)
                {
                    if(strcmp(keyword[i],keyword[j])>0)
                    {
                        strcpy(t,keyword[j]);
                        strcpy(keyword[j],keyword[i]);
                        strcpy(keyword[i],t);
                    }
                }
            }
            */
            int left=0,right=keywordSum-1,mid;
            while(left<=right)
            {
                mid=(left+right)/2;
                if(strcmp(keyword[mid],token)==0)
                {
                    fprintf(fout,"%s\t%s\n",token,token);
                    break;
                }
                if(strcmp(keyword[mid],token)>0)
                    right=mid-1;
                if(strcmp(keyword[mid],token)<0)
                    left=mid+1;
            }
            if(left>right)
            fprintf(fout,"%s\t%s\n","ID",token);
        }
        else if(isdigit(ch)) //����ǳ���
        {
            token[0]=ch;
            j=1;
            ch=getc(fin);
            while(isdigit(ch)||ch=='.')
            {
                token[j++]=ch;//�������������token��
                ch=getc(fin);
            }
            token[j]='\0';
            fprintf(fout,"%s\t%s\n","NUM",token);
        }
        else if(strchr(singleword,ch)>0)//����singleword�����������ҵ�ch
        {
            token[0]=ch;
            token[1]='\0';
            ch=getc(fin);
            fprintf(fout,"%s\t%s\n",token,token);
        }
        else if(strchr(doubleword,ch)>0) //��˫������ҽ�������������ҵ��ʵĵ�һ���ַ�
        {
            token[0]=ch;
            ch=getc(fin);
            if(ch=='='||ch=='&'||ch=='|')//�ٶ�һ���ַ������ж��Ƿ�Ϊ˫�ֽ���ţ�����Ϊ���ֽ����
            {
                token[1]=ch;
                token[2]='\0';
                ch=getc(fin);
            }
            else
                token[1]='\0';
            fprintf(fout,"%s\t%s\n",token,token);
        }
        else if(ch=='/')//����ע�ʹ���
        {
            ch=getc(fin);
            if(ch=='*')
            {
                char ch1;
                ch1=getc(fin);
                do
                {
                    ch=ch1;
                    ch1=getc(fin);
                }
                while((ch!='*'||ch1!='/')&&ch1!=EOF);  //��ch=='*'&&ch1=='/' ���� ch1Ϊ�ļ���β ���˳�ѭ��
                ch=getc(fin);
            }
            else if(ch=='/')
            {
                ch=getc(fin);
                do
                    ch=getc(fin);
                while(ch!='\n'&&ch!=EOF);
                ch=getc(fin);
            }
            else
            {
                token[0]='/';
                token[1]='\0';
                fprintf(fout,"%s\t%s\n",token,token);
            }
        }
        else//�������������
        {
            token[0]=ch;
            token[1]='\0';
            ch=getc(fin);
            es=3;
            fprintf(fout,"%s\t%s\n","ERROR",token);
            printf("%s\t%s\n","ERROR",token);
        }
    }
    fclose(fin);
    fclose(fout);
    return es;
}
