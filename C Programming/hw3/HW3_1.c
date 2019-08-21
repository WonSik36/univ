#include<stdio.h>

float GetSpeed(float);
float MPStoKPH(float);
int main(void)
{
	float sec=0.F,mps=0.F,kph=0.F;
	
	//�ð��� �Է��Ѵ�.
	printf("Input the time: ");
	scanf("%f",&sec);
	
	// m/s�� km/h�� ���� ���Ѵ�.
	mps=GetSpeed(sec);
	kph=MPStoKPH(mps);
	
	//����Ѵ�.
	printf("Your speed = %.2f m/s, or %.2f km/h\n",mps,kph);
	
	return 0;
}

float GetSpeed(float s)
{
	// m/s�� ����Ѵ�
	return 100/s;
}

float MPStoKPH(float ms)
{
	// m/s�� km/h�� �ٲ㼭 ����Ѵ�.
	return ((3600*ms)/1000);
}