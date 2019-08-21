#include<stdio.h>
#define _USE_MATH_DEFINES
#include<math.h>
double Gaussian(double,double,double);

int main(void)
{
	double x=0,mean=0,stdev=0;
	
	//mean,stdev,x를 입력받는다.
	printf("Input mean,stdev, and x: ");
	scanf("%lf %lf %lf",&mean,&stdev,&x);
	
	//출력한다.
	printf("Probability of %.2f from N(%.2f,%.2f) = %f\n",x,mean,stdev,Gaussian(mean,stdev,x));
	

	return 0;
}

double Gaussian(double m, double s, double x)
{
	//Gaussian density의 값을 구한다
	double Gd = (1/(s*sqrt(2*(M_PI))))* exp(-(x-m)*(x-m)/(2*s*s));
	
	return Gd;
}