#include<stdio.h>
#include<string.h>

#define max_size 250

int subnet_size;
int BUFFER_SIZE;
int EXPIRY_TIME;
int diplay_time_out;
int output_type;

struct pair
{
	char key[max_size];
	char value[max_size];
};

void readConfig(struct pair *p)
{
	FILE *fp;
	fp=fopen("config.js","r");
	if(fp==NULL)
	{
		printf("\n file can not be opened");
		return;
	}
	char ch;
	int i,j=0,flag=-1,flag1=1;
	while((ch=fgetc(fp))!=EOF)
	{
		//		printf("%c",ch);
		if(ch==' ' || ch=='\n')
			continue;
		//can add comments handling logic here in extended version
		else if(flag && ch=='{')
		{
			flag=0;
		}
		else if(!flag)
		{
			if(ch==',')
				continue;
			else if(ch=='}')
			{
				flag=1;
			}
			else
			{

				if(!flag1)
				{
					if(ch=='"')
					{
						i=0;
						while((ch=fgetc(fp))!='"')
						{
							p[j].key[i]=ch;
							printf("%c",p[j].key[i]);
							i++;
						}
						printf("\n");
					}
				}
				else if(ch==':')
				{
					flag1=1;
				}
				else if(flag1)
				{
					if(ch=='"')
					{
						i=0;
						while((ch=fgetc(fp))!='"')
						{
							p[j].value[i]=ch;
							printf("%c",p[j].value[i]);						
							i++;
						}
						printf("\n");			
						flag1=0;
						j++;
					}
				}
			}
		}
	}
	int m=0;
	while(m<j)
	{
		i=0;
		if(p[m].key[i]=='\0')
			printf("\n nULL");
		while(p[m].key[i]!='\0')
		{
			printf("%c",p[m].key[i]);
			i++;	
		}
		m++;
	}


}

int main()
{
	struct pair p[max_size];
	readConfig(p);
	return 0;
}
