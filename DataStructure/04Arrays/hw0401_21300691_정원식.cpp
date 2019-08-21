#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#define MAX_SIZE 100

void strnins(char* s, char* t, int i)
{
	char string[MAX_SIZE], *temp = string;

	if(i < 0 && i > strlen(s)){
		fprintf(stderr,"Position is out of bounds\n");
		exit(EXIT_FAILURE);
	}

	if(!strlen(s))
		strcpy(s, t);
	else if (strlen(t)){
		strncpy(temp, s, i);
		temp[i] = 0;
		strcat(temp, t);
		strcat(temp, (s+i));
		strcpy(s, temp);
	}
}

void strninsModified(char *s, char *t, int i)
{
char string[MAX_SIZE];

	if(i < 0 && i > strlen(s)){
		fprintf(stderr,"Position is out of bounds\n");
		exit(EXIT_FAILURE);
	}

	if(!strlen(s))
		strcpy(s, t);
	else if (strlen(t)){
		strncpy(string, s, i);
		string[i] = 0;
		strcat(string, t);
		strcat(string, (s+i));
		strcpy(s, string);
	}
}

char *strninsExtended(char *s, char *t, int i)
{
	char * string = (char*)malloc(strlen(s)+strlen(t)+1);

	if(i < 0 && i > strlen(s)){
		fprintf(stderr,"Position is out of bounds\n");
		exit(EXIT_FAILURE);
	}

	if(!strlen(s))
		strcpy(s, t);
	else if (strlen(t)){
		strncpy(string, s, i);
		string[i] = 0;
		strcat(string, t);
		strcat(string, (s+i));
		strcpy(s, string);
	}
}