#include<stdio.h>

int main(void)
{
	int n=0;
	char c0=0,c1=0,c2=0,c3=0,c4=0;
	int d0=0,d1=0,d2=0,d3=0,d4=0;
	int dec=0;

	printf("Input a positive 5-digit binary number: ");
	scanf("%c%c%c%c%c",&c4,&c3,&c2,&c1,&c0);
	//char���� c��� �������� �޴´�
	d4=c4-'0',d3=c3-'0',d2=c2-'0',d1=c1-'0',d0=c0-'0';
	//char���� c�� ���� integer�� d�� �ٲٸ鼭 �޴´�
	dec=d4*16 + d3*8 + d2*4 + d1*2 + d0*1;
	//�������� �������� ��ȯ�Ѵ�
	printf("Conversion result = %d\n",dec);

	return 0;
}