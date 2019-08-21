#include<stdio.h>

void smoothie(int a[], int n){
	int i = 0,j = 0;
	int idx = a[0];

	while(i<n){
		if(a[i] == a[i+1]){
			for(j = i+1;j < n-1;j++)
				a[j] = a[j+1];
			a[n-1] = -1;
			n--;
		}
		else
			i++;
	}
}