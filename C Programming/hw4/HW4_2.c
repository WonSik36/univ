//#include<stdio.h>
//#include<limits.h>
//
//int main(void){
//	int n=0;
//	int min=INT_MAX,max=INT_MIN;
//
//	//입력의 조건을 얘기하면서 입력할것을 요구한다
//	printf("Enter a series of numbers (<EOF> to stop)\n");
//	
//	//입력과 값에 따라 최대,최소를 구한다
//	while(scanf("%d", &n) != EOF)
//	{
//		if(n>max)
//			max=n;
//		if(n<min)
//			min=n;
//	}
//	
//	//출력한다
//	printf("min = %d\n",min);
//	printf("max = %d\n",max);
//
//	return 0;
//}