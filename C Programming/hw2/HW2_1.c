#include<stdio.h>

int main(void)
{
	float num1,num2;

	printf("Input two float numbers: ");
	scanf("%f %f",&num1,&num2);
	// 두개의 실수를 받는다
	
	printf("%.2f + %.2f = %.2f\n",num1,num2,num1+num2);
	printf("%.2f - %.2f = %.2f\n",num1,num2,num1-num2);
	printf("%.2f * %.2f = %.2f\n",num1,num2,num1*num2);
	printf("%.2f / %.2f = %.2f\n",num1,num2,num1/num2);
	//받은 두개의 실수로 표현한다
	
	return 0;
}