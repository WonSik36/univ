#include <stdio.h>
#include <windows.h>

#define LEN 16
#define K 26	//alphabet number
#define DIGIT 3

void rSort(char* from[], char* to[], int len, int digit);
void cSort(char* from[], char* to[], int len, int k, int digit);
int char2Int(char a);
void printArr(char* arr[], int len);
void copyArr(char* from[], char* to[], int len);

int main(){
	char* A[] = {"COW","DOG","SEA","RUG","ROW","MOB","BOX","TAB","BAR","EAR","TAR","DIG","BIG","TEA","NOW","FOX"};
	char* B[LEN];

	printf("A: ");
	printArr(A,LEN);

	rSort(A,B,LEN,DIGIT);

	system("PAUSE");
}

void rSort(char* from[], char* to[], int len, int digit){
	int i;
	char* arr[len];
	copyArr(from, arr, len);

	for(i=digit-1;i>=0;i--){
		cSort(arr,to,len,K,i);
		copyArr(to, arr, len);
		printf("B: ");
		printArr(arr,LEN);
	}
}

void cSort(char* from[], char* to[], int len, int k, int digit){
	int i;
	int arr[k];

	for(i=0;i<k;i++){
		arr[i] = 0;
	}
	for(i=0;i<len;i++){
		arr[char2Int(from[i][digit])] = arr[char2Int(from[i][digit])] + 1;
	}
	for(i=1;i<k;i++){
		arr[i] = arr[i]+arr[i-1];
	}
	for(i=len-1;i>=0;i--){
		to[arr[char2Int(from[i][digit])]-1] = from[i];
		arr[char2Int(from[i][digit])] = arr[char2Int(from[i][digit])] -1;
	}
}

int char2Int(char a){
	if(a>='a' && a<='z')
		return a-'a';
	else
		return a-'A';
}

void printArr(char* arr[], int len){
	int i;

	for(i=0;i<len;i++){
		printf("\t%s\n",arr[i]);
	}
	printf("\n");
}

void copyArr(char* from[], char* to[], int len){
	int i;
	for(i=0;i<len;i++){
		to[i] = from[i];
	}
}