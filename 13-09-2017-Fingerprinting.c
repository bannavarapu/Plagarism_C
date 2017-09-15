#include <stdio.h>
# include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

struct names
{
	char name[40];
};
struct hashnames
{
	char name[6];
	long long hash;
	long long hashmod;


};

int isprime(long long i)
{
	int j=0,flag=0;
	for(j=2;j<sqrt(i);j++)
	{
		if(i%j==0)
		{
			return 0;
		}
	}
	return 1;
}
long long genprime(long long i)
{
	while(1)
	{
		if(isprime(i))
		{
			return i;
		}
		else
		{
			i++;
		}
	}
}
long word_count(FILE *fp)
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
	if(word_count==0)
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

void remove_stop_words(char word[])
{
	FILE *fp;
	char test[50];
	fp=fopen("stop_words.txt","r");
	fseek(fp,0,SEEK_SET);
	for(int i=0;i<319;i++)
	{
		fscanf(fp,"%s",test);	
		if(!(strcmp(test,word)))
		{
			word[0]='\0';
			break;
		}
	}
}
void generate_hashvalues(struct hashnames array[],char str[],long long prime )
{
	long i=0;
	long j=0;
	long k=0;
	long long pro=0;
	for(i=0;i<strlen(str)-4;i++)
	{
		pro=0;
		for(j=i,k=0;j<i+5;j++)
		{
			// printf("%c",str[j]);
			array[i].name[k]=str[j];
			pro+=((int)str[j])*(pow(5,k));
			k++;
		}
		array[i].name[k]='\0';
		array[i].hash=pro;
		array[i].hashmod=(pro%prime);
		// printf("%li\n",array[i].hashmod );
	}
}


void main()
{
	FILE *fp1;
	FILE *fp2;
	fp1=fopen("text1.txt","r");
	fp2=fopen("text2.txt","r");
	long count1;
	long count2;
	count1=word_count(fp1);
	count2=word_count(fp2);
	if(count1!=0 && count2!=0)
	{
	struct names name1[count1];
	struct names name2[count2];
	long j=0;
	long i=0;
	long k=0;
	char c;
	fseek(fp1,0,SEEK_SET);
	fseek(fp2,0,SEEK_SET);
	long long len1=0;
	long long len2=0;
	char *longarray1;
	char *longarray2;

	for(i=0;i<count1;i++)
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
				name1[i].name[j]=tolower(c);
				j++;
			}
		}
		name1[i].name[j]='\0';
		remove_stop_words(name1[i].name);
	}
	for(i=0;i<count2;i++)
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
				name2[i].name[j]=tolower(c);
				j++;
			}
		}
		name2[i].name[j]='\0';
		remove_stop_words(name2[i].name);
	}
	for(i=0;i<count1;i++)// for finding the length of array to append all the words into it
	{
		if(strlen(name1[i].name)>0)
		{
			len1+=strlen(name1[i].name);
		}	
	}
	for(i=0;i<count2;i++)
	{
		if(strlen(name2[i].name)>0)
		{
			len2+=strlen(name2[i].name);
		}
	}
	if(len1>5 || len2>5){
	longarray1=malloc(sizeof(char)*(len1+1));
	longarray2=malloc(sizeof(char)*(len2+1));
	for(i=0,k=0;i<count1;i++)
	{
		if(strlen(name1[i].name)>0)
		{
			for(j=0;name1[i].name[j]!='\0';j++)
			{
				longarray1[k]=name1[i].name[j];
				k++;
			}
		}
	}
	longarray1[k]='\0';
	for(i=0,k=0;i<count2;i++)
	{
		if(strlen(name2[i].name)>0)
		{
			for(j=0;name2[i].name[j]!='\0';j++)
			{
				longarray2[k]=name2[i].name[j];
				k++;
			}
		}
	}
	longarray2[k]='\0';

	struct hashnames *hashing1;
	struct hashnames *hashing2;
	 hashing1=malloc(sizeof(struct hashnames)*(len1-4));
	hashing2=malloc(sizeof(struct hashnames)*(len2-4));

	
	long long prime=genprime((len1>len2?len1:len2)*100);
	// printf("%lli\n",prime );
	
	generate_hashvalues(hashing1,longarray1,prime);
	generate_hashvalues(hashing2,longarray2,prime);

	long long common=0;
	for(i=0;i<(len1-4);i++)
	{
		for(j=0;j<(len2-4);j++)
		{
			if(hashing1[i].hashmod==hashing2[j].hashmod)
			{
				common++;
			}
		}
	}
	double match=(double)(2*common)/(double)(len1+len2-8);
	printf("%0.2lf",(match*100));

}
else
{
	printf("%s\n","Files are too short to form finger print" );
}	
}
else
{
	printf("%s\n","One or both of them are empty" );
}
}

