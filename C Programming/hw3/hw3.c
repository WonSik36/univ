/*
(Fahrenheit)=(Celsius)*1.8 + 32
*/
#include<stdio.h>

int main(void)
{
	float f,c;
	
	//¼·¾¾ ÀÔ·Â
	printf("Put temperature by Celsius: ");
	scanf("%f",&c);
	//¼·¾¾¸¦ È­¾¾·Î º¯È¯
	f=c*1.8 + 32;
	//Ãâ·Â
	printf("The tempreature is same with %f degrees Fahrenheit\n",f);

	return 0;
}