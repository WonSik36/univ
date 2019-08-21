#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DataFile "phonebook.txt"
#define MaxEntry 256

// phonebook data
typedef struct {
	char name[64];
	char number[32];
} PhoneBookEntry;

// global variables
PhoneBookEntry phonebook[MaxEntry];
int noEntry = 0;

// function declarations
int ReadPhoneBook(char *filename);
void PrintPhoneBook();
int FindName(char *string);

int main()
{
	char name[64];
	int idx = 0;
	int ret = 0;

	ret = ReadPhoneBook(DataFile);			// read phonebook from a text file
	if(ret < 0){
		printf("Failed to read %s!\n", DataFile);
		exit(-1);
	}

	PrintPhoneBook();

	while(1){
    printf("\nInput name to find (or CTRL-Z to quit) : ");
    ret = scanf("%s", name);
    if(ret < 1)
    	break;

    idx = FindName(name);
    if(idx < 0)
    	printf("==> Failed to find %s from the phonebook!\n", name);
    else
    	printf("==> Phone number of %s is %s.\n", name, phonebook[idx].number);
	}

	printf("Bye!\n");

	return 0;
}

int ReadPhoneBook(char *filename)
{
	int n=0,ret=0;
	//open file
	FILE *fp= fopen(filename,"rt");
	//read phonebook data from a text file.
	while(1){
		ret=fscanf(fp,"%s %s",&phonebook[n].name,&phonebook[n].number);
		if(ret==EOF)
			break;
		n++;
	}
	noEntry=n;
	//returns 0 in successful case
	//return -1 otherwise
	
	if(feof(fp)!=0){
		fclose(fp);
		return 0;
	}
	else{
		fclose(fp);
		return -1;
	}
}

void PrintPhoneBook()
{
	int i = 0;

	printf("Totally, %d entries\n", noEntry);

	for(i = 0 ; i < noEntry; i++)
		printf("\t%-16s\t%s\n", phonebook[i].name, phonebook[i].number);
}

int FindName(char *name)
{
	int n=0;
	
	//Searches the name from aNames.
	for(n=0;n<=noEntry;n++){
		//returns the index of the name if it succeeds
		if(strcmp(name,phonebook[n].name)==0)
			return n;
	}
	//returns -1 if it fails to find the name.
	return -1;
}
