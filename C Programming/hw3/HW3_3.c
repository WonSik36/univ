#include<stdio.h>
void Get3LSD(int,int*,int*,int*);

int main(void)
{
	int x=0;
	int d3=0,d2=0,d1=0;
	
	//x�� ���� �Է��Ѵ�
	printf("Input a 3-digit integer: ");
	scanf("%d",&x);
	
	//�Լ��� ����Ѵ�
	Get3LSD(x,&d3,&d2,&d1);
	
	//����Ѵ�
	printf("%d --> (%d %d %d)\n",x,d3,d2,d1);
	
	return 0;
}

void Get3LSD(int x, int *d3, int *d2, int *d1)
{
	// d3,d2,d1�� ���� ���Ѵ�
	*d3= x/100;
	*d2= (x%100)/10;
	*d1= x%10;

	return;
}