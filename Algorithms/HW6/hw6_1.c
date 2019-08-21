#include <stdio.h>
#include <windows.h>

#define K 7
#define LEN 11

void cSort(int from[], int to[], int len, int k);
void printArr(int arr[], int len);

int main(){
	int A[] = {6,0,2,0,1,3,4,6,1,3,2};
	int B[LEN];
	cSort(A,B,LEN,K);

	printf("A: ");
	printArr(A,LEN);
	printf("B: ");
	printArr(B,LEN);
	system("PAUSE");
}

void cSort(int from[], int to[], int len, int k){
	int i;
	int arr[k];

	for(i=0;i<k;i++){
		arr[i] = 0;
	}
	printArr(from,len);
	printArr(arr,k);
	printf("\n");
	for(i=0;i<len;i++){
		arr[from[i]] = arr[from[i]] + 1;
	}
	printArr(from,len);
	printArr(arr,k);
	printf("\n");
	for(i=1;i<k;i++){
		arr[i] = arr[i]+arr[i-1];
	}
	printArr(from,len);
	printArr(arr,k);
	printf("\n");
	for(i=len-1;i>=0;i--){
		to[arr[from[i]]-1] = from[i];
		arr[from[i]] = arr[from[i]] -1;
	}
	printArr(from,len);
	printArr(to,len);
	printArr(arr,k);
	printf("\n");
}

void printArr(int arr[], int len){
	int i;

	for(i=0;i<len;i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
}