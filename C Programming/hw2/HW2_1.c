#include<stdio.h>

int main(void)
{
	float num1,num2;

	printf("Input two float numbers: ");
	scanf("%f %f",&num1,&num2);
	// �ΰ��� �Ǽ��� �޴´�
	
	printf("%.2f + %.2f = %.2f\n",num1,num2,num1+num2);
	printf("%.2f - %.2f = %.2f\n",num1,num2,num1-num2);
	printf("%.2f * %.2f = %.2f\n",num1,num2,num1*num2);
	printf("%.2f / %.2f = %.2f\n",num1,num2,num1/num2);
	//���� �ΰ��� �Ǽ��� ǥ���Ѵ�
	
	return 0;
}