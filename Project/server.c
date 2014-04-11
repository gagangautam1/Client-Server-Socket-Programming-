#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
//#include <netdb.h>

#include <iostream>
#include <string>
#include <ctype.h>
#include <string.h>
#include<fstream>
#include <pthread.h>
using namespace std;

char str[256];
void *charCount(void *param);
void *wordCount(void *param);
void *sentenceCount(void *param);
void *characterOccurence(void *param);
void *caseConversion(void *param);

void error(char *msg)
{
perror(msg);
exit(1);
}

int main(int argc, char *argv[])
{
int sockfd, newsockfd, portno,clilen;
char buff[256];
struct sockaddr_in serv_addr, cli_addr;
int n;
FILE * stderr;
pid_t pid;
pthread_t tid;
pthread_attr_t attr;

if(argc < 2){
	fprintf(stderr,"Error no port provided");
	exit(1);
}

sockfd = socket(AF_INET, SOCK_STREAM,0);

if(sockfd<0)
{
	error("ERROR opening socket");
}

bzero((char *) &serv_addr, sizeof(serv_addr));

portno = atoi(argv[1]);

serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = INADDR_ANY;
serv_addr.sin_port = htons(portno);
if(bind(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))<0){
	error("ERROR on binding");
}

listen(sockfd,5);
clilen = sizeof(cli_addr);

newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);

if(newsockfd<0)
{
	error("ERROR on accept");
}

bzero(buff,256);
n=read(newsockfd,buff,255);
if(n<0){
 error("Error in reading socket");
}

strncpy(str,buff,256);
printf("Message Recieved: %s\n",str);

/*pthread_attr_init(&attr);
pthread_create(&tid,&attr,characterOccurence,NULL);
pthread_join(tid,NULL);*/

pthread_attr_init(&attr);
pthread_create(&tid,&attr,caseConversion,NULL);
pthread_join(tid,NULL);

/*pthread_attr_init(&attr);
pthread_create(&tid,&attr,charCount,NULL);
pthread_join(tid,NULL);

pthread_attr_init(&attr);
pthread_create(&tid,&attr,wordCount,NULL);
pthread_join(tid,NULL);

pthread_attr_init(&attr);
pthread_create(&tid,&attr,sentenceCount,NULL);
pthread_join(tid,NULL);*/

n= write(newsockfd,str,256);
if(n<0){
	error("Error in writng socket");
}



return 0;

}

void *characterOccurence(void *param)
{
int a_count,b_count;
//cout<<endl;
//cout<<"Alphabet Occurence:"<<endl;
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
//cout<<ch1<<" = "<<a_count<<"; "<<ch2<<" = "<<b_count<<endl;
	}
}


void *caseConversion(void *param)
{
//cout<<endl;
//cout<<"Converted Case: ";
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
 //  cout<< str << endl;

}

void *charCount(void *param)
{
//cout<<endl;
int noOfChar=0;
for(int i = 0; i < strlen(str); i++)
	{
		if(isspace(str[i]))
		{}
		else if(str[i] != '\0' || str[i] != '\n' || str[i] != '\r' || str[i] != '\t')
			noOfChar++;
	} 
//cout<<"Number of Characters: "<<noOfChar<<endl;
}

void *wordCount(void *param)
{
//cout<<endl;
int noOfWords=0;
char *word;
word = strtok(str," ,.");
		while(word != NULL)
		{
			noOfWords++;
			word = strtok(NULL," ,.");
		}
//cout<<"Number of words: "<<noOfWords<<endl;
}

void *sentenceCount(void *param)
{
//cout<<endl;
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
//cout<<"Number of Senences: "<<noOfSentences<<endl;
}
