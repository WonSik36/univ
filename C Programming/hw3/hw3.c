/*
(Fahrenheit)=(Celsius)*1.8 + 32
*/
#include<stdio.h>

int main(void)
{
	float f,c;
	
	//���� �Է�
	printf("Put temperature by Celsius: ");
	scanf("%f",&c);
	//������ ȭ���� ��ȯ
	f=c*1.8 + 32;
	//���
	printf("The tempreature is same with %f degrees Fahrenheit\n",f);

	return 0;
}