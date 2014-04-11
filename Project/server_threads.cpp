#include <iostream>
#include <string>
#include <ctype.h>
#include <string.h>
#include<fstream>
#include<algorithm>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>

using namespace std;
char str[256];
void *charCount(void *param);
void *wordCount(void *param);
void *sentenceCount(void *param);
void *characterOccurence(void *param);
void *caseConversion(void *param);

int main(int argc, char *argv[]) 
{
pid_t pid;
pthread_t tid;
pthread_attr_t attr;
cout << "Enter string: ";
cin.getline(str,256);

pthread_attr_init(&attr);
pthread_create(&tid,&attr,characterOccurence,NULL);
pthread_join(tid,NULL);

pthread_attr_init(&attr);
pthread_create(&tid,&attr,caseConversion,NULL);
pthread_join(tid,NULL);

pthread_attr_init(&attr);
pthread_create(&tid,&attr,charCount,NULL);
pthread_join(tid,NULL);

pthread_attr_init(&attr);
pthread_create(&tid,&attr,wordCount,NULL);
pthread_join(tid,NULL);

pthread_attr_init(&attr);
pthread_create(&tid,&attr,sentenceCount,NULL);
pthread_join(tid,NULL);
   return 0;
}


void *characterOccurence(void *param)
{
int a_count,b_count;
cout<<endl;
cout<<"Alphabet Occurence:"<<endl;
for(char ch1 = 'A', ch2 = 'a'; ch1<='Z',ch2<='z'; ch1++,ch2++)
	{
		a_count = 0;
		b_count = 0;
		for(int i = 0; i < strlen(str); i++)
		{
			if(str[i] == ch1)
				a_count++;
			if(str[i] == ch2)
				b_count++;
		}
cout<<ch1<<" = "<<a_count<<"; "<<ch2<<" = "<<b_count<<endl;
	}
}


void *caseConversion(void *param)
{
cout<<endl;
cout<<"Converted Case: ";
for(int i = 0; i < strlen(str); i++)
	{
       if(isupper(str[i]))
		{
			str[i] = tolower(str[i]);
		}
		else if(islower(str[i]))
		{
			str[i] = toupper(str[i]);
		}
	}
   cout<< str << endl;

}

void *charCount(void *param)
{
cout<<endl;
int noOfChar=0;
for(int i = 0; i < strlen(str); i++)
	{
		if(isspace(str[i]))
		{}
		else if(str[i] != '\0' || str[i] != '\n' || str[i] != '\r' || str[i] != '\t')
			noOfChar++;
	} 
cout<<"Number of Characters: "<<noOfChar<<endl;
}

void *wordCount(void *param)
{
cout<<endl;
int noOfWords=0;
char *word;
word = strtok(str," ,.");
		while(word != NULL)
		{
			noOfWords++;
			word = strtok(NULL," ,.");
		}
cout<<"Number of words: "<<noOfWords<<endl;
}

void *sentenceCount(void *param)
{
cout<<endl;
int noOfSentences=0;
for(int i = 0; i < strlen(str); i++)
{
	if(str[i] == '.')
		{
			if(str[i+1] != '.')
			noOfSentences++;
		}
}
if(noOfSentences == 0)
noOfSentences = 1;
cout<<"Number of Senences: "<<noOfSentences<<endl;
}
