#include <stdio.h>
#include <iostream>
#include <string.h>
struct word
{
	char name[100];
	int num;
	struct word*next;
};

int read(struct word*&head)
{
    FILE *fp;
    if((fp=fopen("input.txt","r"))==NULL)
    {
    	exit(0);
	}
	int n=0;
	char ch,temp[30];
	struct word*p;
	while(feof(fp)!=0)
	{
		int i=0;
        ch=fgetc(fp);
        temp[0]=' '; 
        while((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||temp[0]==' ')
        {
            if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z')
            {
                temp[i]=ch;
                i++;
            }
            ch=fgetc(fp);
            if(feof(fp)) break;
        }
        temp[i]='\0';
        p=head->next;
        while(p)
        {
            if(!_stricmp(temp,p->name)) 
            { 
                p->num++;
                n++; 
				break;
            } 
            p=p->next;
        }
        if(!p&&temp[0]!='\0')
        {
            p=new word;
            strcpy(p->name,temp);
            p->num=1;
            n++;
            p->next=head->next;
            head->next=p;
        }
	}
	return n;
}

int main()
{
	char n[100];
	int a;
	struct word *head;
	head=new word;
	head->next=NULL;
	a=read(head);
	printf("%d",&a);
	return 0;
}
