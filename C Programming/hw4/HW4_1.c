//#include<stdio.h>
//
//int main(void)
//{
//	int n=0,i=0;
//	int a=0,b=0;
//
//	//���ڸ� �Է¹޴´�
//	printf("Input an odd number that size of diamond between 3 and 9: ");
//	scanf("%d", &n);
//
//	//���ǿ� �����ʴ� ��� ���Է��ϵ��� �䱸�Ѵ�
//	while(1){
//		if((n>=3)&&(n<=9)&&(n%2==1))
//			break;
//		else{
//			printf("Reinput: ");
//			scanf("%d", &n);
//		}}
//
//	//�ٿ� ���� *�� �����ϴ� �ܰ踦 ǥ���Ѵ�
//	for(i=0;i<(n/2+1);i++){
//		for(a=0;a<(n-2*i)/2;a++)
//			putchar(' ');
//		for(b=2*i+1;b>0;b--)
//			putchar('*');
//		printf("\n");
//	}
//	
//	//�ٿ� ���� *�� �����ϴ� �ܰ踦 ǥ���Ѵ�
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