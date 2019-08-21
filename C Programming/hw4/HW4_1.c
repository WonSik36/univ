//#include<stdio.h>
//
//int main(void)
//{
//	int n=0,i=0;
//	int a=0,b=0;
//
//	//숫자를 입력받는다
//	printf("Input an odd number that size of diamond between 3 and 9: ");
//	scanf("%d", &n);
//
//	//조건에 맞지않는 경우 재입력하도록 요구한다
//	while(1){
//		if((n>=3)&&(n<=9)&&(n%2==1))
//			break;
//		else{
//			printf("Reinput: ");
//			scanf("%d", &n);
//		}}
//
//	//줄에 따라 *이 증가하는 단계를 표현한다
//	for(i=0;i<(n/2+1);i++){
//		for(a=0;a<(n-2*i)/2;a++)
//			putchar(' ');
//		for(b=2*i+1;b>0;b--)
//			putchar('*');
//		printf("\n");
//	}
//	
//	//줄에 따라 *이 감소하는 단계를 표현한다
//	for(i=n/2;i>0;i--){
//		for(a=0;a<(n-2*i)/2+1;a++)
//			putchar(' ');
//		for(b=2*i-1;b>0;b--)
//			putchar('*');
//		printf("\n");
//	}
//
//	return 0;
//}