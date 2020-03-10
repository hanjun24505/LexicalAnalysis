#include "LexicalAnalysis.h"

char *keyword[keywordSum]={"auto","break","call","case","char","const","continue","default","do","double","else","enum","extern",
"float","for","function","goto","if","int","long","read","register","return","short","signed","sizeof","static",
"struct","switch","typedef","union","unsigned","void","volatile","while","write"};
//定义单分界符
char singleword[50]="+-*\(){}[];'\"',:.'%^";
//定义双分界符
char doubleword[10]="><=!&|";

extern char Scanin[300],Scanout[300];
extern FILE *fin,*fout;//指向输入输出文件的指针

int TESTscan()
{
    char ch,token[40],*t;//ch为每次读入的字符，token用于保存识别出的单词
    int es=0,j,n;
    printf("-------------------------------------------------------------------------\n");
    printf("请输入源程序文件名字(test1.txt test2.txt test3.txt):");
    scanf("%s",Scanin);
    printf("-------------------------------------------------------------------------\n");
    printf("请输入词法分析输出文件名字(out1.txt out2.txt out3.txt):");
    scanf("%s",Scanout);
    printf("-------------------------------------------------------------------------\n");
    if((fin=fopen(Scanin,"r"))==NULL)
    {
        printf("打开源程序文件出错！\n");
        return 1;
    }
    if((fout=fopen(Scanout,"w"))==NULL)
    {
        printf("\n打开词法分析输出文件出错！\n");
        return 2;
    }
    ch=getc(fin);//取一个字符
    while(ch!=EOF)//没有到文件结尾
    {
        while(ch==' '||ch=='\n'||ch=='\t') //如果是空格，换行，则直接跳过
            ch=getc(fin);
        if(isalpha(ch)||ch=='_')//如果ch是字母,则进行标识符处理
        {
           token[0]=ch;
           j=1;
           ch=getc(fin);
           while(isalnum(ch)||ch=='_') //如果是字母数字
           {
               token[j++]=ch;
               ch=getc(fin);
           }
            token[j]='\0';//标识符组合结束
            //查关键字
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
        else if(isdigit(ch)) //如果是常数
        {
            token[0]=ch;
            j=1;
            ch=getc(fin);
            while(isdigit(ch)||ch=='.')
            {
                token[j++]=ch;//组合整数保存在token中
                ch=getc(fin);
            }
            token[j]='\0';
            fprintf(fout,"%s\t%s\n","NUM",token);
        }
        else if(strchr(singleword,ch)>0)//能在singleword这个数组里查找到ch
        {
            token[0]=ch;
            token[1]='\0';
            ch=getc(fin);
            fprintf(fout,"%s\t%s\n",token,token);
        }
        else if(strchr(doubleword,ch)>0) //在双分里查找界符这个数组里查找单词的第一个字符
        {
            token[0]=ch;
            ch=getc(fin);
            if(ch=='='||ch=='&'||ch=='|')//再读一个字符才能判断是否为双分界符号，否则为单分界符号
            {
                token[1]=ch;
                token[2]='\0';
                ch=getc(fin);
            }
            else
                token[1]='\0';
            fprintf(fout,"%s\t%s\n",token,token);
        }
        else if(ch=='/')//进行注释处理
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
                while((ch!='*'||ch1!='/')&&ch1!=EOF);  //当ch=='*'&&ch1=='/' 或者 ch1为文件结尾 就退出循环
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
        else//以上情况都不是
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
