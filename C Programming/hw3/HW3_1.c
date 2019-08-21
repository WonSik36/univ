#include<stdio.h>

float GetSpeed(float);
float MPStoKPH(float);
int main(void)
{
	float sec=0.F,mps=0.F,kph=0.F;
	
	//시간을 입력한다.
	printf("Input the time: ");
	scanf("%f",&sec);
	
	// m/s와 km/h의 값을 구한다.
	mps=GetSpeed(sec);
	kph=MPStoKPH(mps);
	
	//출력한다.
	printf("Your speed = %.2f m/s, or %.2f km/h\n",mps,kph);
	
	return 0;
}

float GetSpeed(float s)
{
	// m/s를 출력한다
	return 100/s;
}

float MPStoKPH(float ms)
{
	// m/s를 km/h로 바꿔서 출력한다.
	return ((3600*ms)/1000);
}