#include <stdio.h>
# include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

struct name_count
{
	char name[50];
	int count;
};

long get_word_count(FILE *fp)
{
	long word_count=0;
	long characters=0;
	char c;

	while((c=fgetc(fp))!=EOF)
	{
		if(c==' ' || c=='\n' ||c==EOF)
		{
			word_count++;
		}
		else
		{
			characters++;
		}
	}
	if(word_count==1)
	{
		if(characters==0)
		{
			return word_count;
		}
		else
		{
			return (word_count+1);
		}
	}
	else
	{
		return (word_count+1);
	}
}

void frequency(struct name_count names1[],long word_count1)
	{
		int i=0;
		int j=0;
		for(i=0;i<word_count1;i++)
		{	
			names1[i].count=1;
			for(j=i+1;j<word_count1;j++)
			{
				if(!(strcmp(names1[i].name,names1[j].name)))
				{
					names1[j].name[0]='\0';
					names1[i].count++;
				}
			}
		}
	}
void main()
{
	FILE *fp1;
	FILE *fp2;
	fp1=fopen("text1.txt","r");
	fp2=fopen("text2.txt","r");
	long word_count1;
	long word_count2;
	word_count1=get_word_count(fp1);
	word_count2=get_word_count(fp2);
	// printf("%lli %lli\n",word_count1,word_count2 );
	if(word_count1!=1 && word_count2!=1)
	{
	fseek(fp1,0,SEEK_SET);
	fseek(fp2,0,SEEK_SET);
	long int i=0;
	long int j=0;
	char c;
	double percent_match;
	struct name_count names1[word_count1];
	struct name_count names2[word_count2];

	double den1,den2;
	double num;
	for(i=0;i<word_count1;i++)
	{	
		j=0;
		while((c=fgetc(fp1))!=EOF)
		{
			if(c==' '||c=='\n' || c==EOF)
			{
				break;
			}

			else if((c>='a'&&c<='z')||(c>='A' && c<='Z')||(c>='0' && c<='9')|| c=='_')

			{
				names1[i].name[j]=tolower(c);
				j++;
			}
		}
		names1[i].name[j]='\0';
	}
	for(i=0;i<word_count2;i++)
	{	
		j=0;
		while((c=fgetc(fp2))!=EOF)
		{
			if(c==' '||c=='\n' || c==EOF)
			{
				break;
			}
			else if((c>='a'&&c<='z')||(c>='A' && c<='Z')||(c>='0' && c<='9')|| c=='_')

			{
				names2[i].name[j]=tolower(c);
				j++;
			}
		}
		names2[i].name[j]='\0';
	}
	
	frequency(names1,word_count1);
	frequency(names2,word_count2);
	
	for(i=0;i<word_count1;i++)
	{
		for(j=0;j<word_count2;j++)
		{
			if(!(strcmp(names1[i].name,names2[j].name)))
			{
				if((strlen(names1[i].name)>0))
				{
					num+=names1[i].count*names2[j].count;
				}
			}
		}
	}
	for(i=0;i<word_count1;i++)
	{
		if(strlen(names1[i].name)>0)
		{
			den1+=(names1[i].count)*(names1[i].count);
		}
	}
	for(i=0;i<word_count2;i++)
	{
		if(strlen(names2[i].name)>0)
		{
			den2+=(names2[i].count)*(names2[i].count);
		}
	}
		percent_match=(double)(num)/(double)(sqrt(den1)*sqrt(den2));
		printf("%s %.2lf \n", "Percent match between the files is ",(percent_match*100));
	
	}
	else
	{
		printf("%s\n","One or both of them are empty files" );
	}
	

	
}
