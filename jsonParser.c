#include<stdio.h>
#include<string.h>

#define max_size 250

int subnet_size;
int BUFFER_SIZE;
int EXPIRY_TIME;
int display_time_out;
int output_type;

struct pair
{
	char key[max_size];
	char value[max_size];
};

int convert_value_to_int(char *ch)
{
	int i=0;
	while(ch[i]!='\0')
		i++;
	int val=0,place=1,len=i;
	for(i=len-1;i>=0;i--)
	{
		val+=place*(ch[i]-48);
		place*=10;
	}
	return val;
}

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
	int i,j=0,flag=-1,flag1=0;
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
				break;
			}
			else if(ch==':')
			{
			//	printf("\n here");
				flag1=1;
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
					//		printf("k=%c",p[j].key[i]);
							i++;
						}
					//	ch=fgetc(fp);
					//	printf("ch=%c",ch);
					}
				}
				else if(flag1)
				{
					if(ch=='"')
					{
						i=0;
						while((ch=fgetc(fp))!='"')
						{
							p[j].value[i]=ch;
			//				printf("v=%c",p[j].value[i]);						
							i++;
						}
					//	ch=fgetc(fp);
					//	printf("ch=%c",ch);			
						flag1=0;
						j++;
					}
				}
			}
		}
	}
	int m,val;
	for(m=0;m<j;m++)
	{
		i=0;
		val=convert_value_to_int(p[m].value);
		if(strcmp(p[m].key,"SubnetMask")==0)
		{
			subnet_size=val;
		}
		else if(strcmp(p[m].key,"BufferPoolSize")==0)
		{
			BUFFER_SIZE=val;	
		}
		else if(strcmp(p[m].key,"CleanTimeout")==0)
		{
			EXPIRY_TIME=val;
		}
		else if(strcmp(p[m].key,"PrintTimeout")==0)
		{
			display_time_out=val;
		}
		else
		{
			output_type=val;
		}
	}
}

int main()
{
	struct pair p[max_size];
	readConfig(p);
	printf("\n%d--%d--%d--%d--%d",subnet_size,BUFFER_SIZE,EXPIRY_TIME,display_time_out,output_type);
	return 0;
}
