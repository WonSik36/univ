#include<stdio.h>

int main(void)
{
	int num,a,b,c,d,e;

	printf("Input 5-digit integer number: ");
	scanf("%d",&num);
	//5자리 숫자를 받는다

	a=num/10000;
	b=(num%10000)/1000;
	c=(num%1000)/100;
	d=(num%100)/10;
	e=num%10;
	//각 자리의 숫자를 받는다

	printf("%d %d %d %d %d\n",a,b,c,d,e);
	//출력한다

	return 0;
}