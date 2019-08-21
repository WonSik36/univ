#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	int n=0,num=0;
	int* arr=NULL;

	printf("How many intergers?	");//Input length of array
	scanf("%d",&n);
	num=n;
	
	arr=(int*)malloc(sizeof(int)*n);//memory allocation to arr

	printf("Input integer numbers.\n");
	
	//Input values
	for(n-=1;n>=0;n--)
		scanf("%d",&arr[n]);

	printf("Numbers in reverse order: ");
	
	//print values
	for(n=0;n<num;n++)
		printf("%d ",arr[n]);

	printf("\n");
	
	return 0;
}