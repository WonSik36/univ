#include<stdio.h>

int main(void)
{
	int i=0, n=0, testEOF=0;
	int arr[10];

	//�Է��� �䱸�Ѵ�
	printf("Input integer numbers.\n");

	//�ΰ��� ����(10�����Է�, EOF�� �Է�)�� �ϳ��� �����ϸ� �������ְ��Ѵ�
	while((i!=10)&&(testEOF=scanf("%d",&n)!=EOF)){
		arr[i]=n;
		i++;
	}
	i--;
	
	//����Ѵ�
	printf("Numbers in reverse order: ");
	for(;i>=0;i--)
		printf("%d ",arr[i]);
	printf("\n");

	return 0;
}