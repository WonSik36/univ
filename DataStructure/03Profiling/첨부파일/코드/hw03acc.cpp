#include<stdio.h>
#include<time.h>
#define MAX_SIZE 16385

void QuickSort(int arr[], int left, int right);

void main(void)
{
	int i, j, n=1, step=2;
	int a[MAX_SIZE];
	double duration;
	FILE* fp=fopen("quicksort.txt","wt");

	printf("       n      repetitions      time\n");
	fprintf(fp,"       n      repetitions      time\n");
	for(j=0; j<15; j++,n*=step){
		long repetitions = 0;
		clock_t start = clock();
		do{
			repetitions++;

			for(i=0;i<n;i++)
				a[i] = n - i;

			QuickSort(a, 0, n-1);
		}while(clock() - start < 10000);

		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;

		duration /= repetitions;
		printf("%6d     %9d     %f\n", n, repetitions, duration);
		fprintf(fp, "%6d     %9d     %f\n", n, repetitions, duration);
	}
	fclose(fp);
	return;
}