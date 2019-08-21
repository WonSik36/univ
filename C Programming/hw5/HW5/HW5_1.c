#include<stdio.h>

int main(void)
{
	int i=0, n=0, testEOF=0;
	int arr[10];

	//입력을 요구한다
	printf("Input integer numbers.\n");

	//두가지 조건(10개의입력, EOF의 입력)중 하나를 만족하면 나갈수있게한다
	while((i!=10)&&(testEOF=scanf("%d",&n)!=EOF)){
		arr[i]=n;
		i++;
	}
	i--;
	
	//출력한다
	printf("Numbers in reverse order: ");
	for(;i>=0;i--)
		printf("%d ",arr[i]);
	printf("\n");

	return 0;
}