#include<stdio.h>

int main(void)
{
	int num,a,b,c,d,e;

	printf("Input 5-digit integer number: ");
	scanf("%d",&num);
	//5�ڸ� ���ڸ� �޴´�

	a=num/10000;
	b=(num%10000)/1000;
	c=(num%1000)/100;
	d=(num%100)/10;
	e=num%10;
	//�� �ڸ��� ���ڸ� �޴´�

	printf("%d %d %d %d %d\n",a,b,c,d,e);
	//����Ѵ�

	return 0;
}