#include <stdio.h>
# include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

long long charcount(FILE* fp)// this function gets a pointer of an opened file, returns the character count 
{
	char c;
	long long count=0;

	while((c=fgetc(fp))!=EOF)
	{
		if((c>='a'&&c<='z')||(c>='A' && c<='Z')||(c>='0' && c<='9')||(c=='\n'))
		{
			count++;
		}
	}
	return (count+1);
}

int to_characterarray(FILE*fp,char *chararray )
{
	long long int i=0;
	char c;
	while((c=fgetc(fp))!=EOF)
	{
		if((c>='a'&&c<='z')||(c>='A' && c<='Z')||(c>='0' && c<='9')||c=='\n')
		{
			if(c!='\n')
			{
				chararray[i]=tolower(c);
				i++;
			}
		}
	}
	chararray[i]='\0';
	if(i>0)
	{
		return (1);
	}
	else
	{
		return(-1);
	}

}
long long compare(char a[],char b[],long i,long j)
{
	// long long l=(strlen(a)<strlen(b)?strlen(a):strlen(b));
	long long common=0;
	while(i<strlen(a)&& j<strlen(b))
	{
		if(a[i]==b[j])
		{
			// printf("%c\n",a[i] );
			// printf("%s\n","Hey" );
			common++;
			i++;
			j++;
		}
		else
		{
			break;
		}
	}
	// printf("%lli\n",common );
	return (common);
}

int main()
{
	FILE* fp1;
	FILE* fp2;
	char filename1[]="text1.txt";
	char filename2[]="text2.txt";
	fp1=fopen(filename1,"r");
	fp2=fopen(filename2,"r");
	char c1;
	char c2;
	char *charc1;
	char *charc2;	
	long long count1=0;
	long long count2=0;

	int i1;
	int i2;

	long long i;
	long long j;
	long long min=0;
	long long common;
	double percent_match;
	if(fp1!=NULL && fp2!=NULL)
	{
		count1=charcount(fp1);
		count2=charcount(fp2);
		// printf("%lli %lli\n",count1,count2 );
		if(count1==1 || count2==1)
		{
			printf("%s\n","One or both the files are empty or contains special characters" );
		}
		else
		{
			charc1=malloc(sizeof(char)*count1+1);
			charc2=malloc(sizeof(char)*count2+1);
			fseek(fp1,0,SEEK_SET);
			fseek(fp2,0,SEEK_SET);
			i1=to_characterarray(fp1,charc1);
			i2=to_characterarray(fp2,charc2);
			if(i1==(-1) && i2==(-1))
			{
				printf("%s\n","One or both files have only special characters" );
			}

			else
			{
				for(i=0;i<count1;i++)
				{
					for(j=0;j<count2;j++)
					{
						if(charc1[i]==charc2[j])
						{
							common=compare(charc1,charc2,i,j);
							// printf("%lli\n",common );
							if(common>min)
							{
								min=common;
								// printf("%lli\n",min );
							}

						}
					}
				}
//				printf("%lli %lli %lli\n",min,count1,count2 );

				percent_match=((2*min)/(double)(count1+count2-2));//*100;
				 percent_match=(double)(percent_match*100);
				printf("%s %.2lf\n","Percentage match between these files is ",percent_match );
			}
		}
	}

	else
	{
		printf("%s\n","Something wrong while opening files" );
	}
}
