#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

typedef struct{
	int * arr;
}S;

int main(){
	int arr_1[5];	// 배열 선언
	S * s = (S*)malloc(sizeof(S));	// 포인터 변수 선언
	int i;

	for(i = 0; i < 5; i++) {
		arr_1[i] = i+1;	// 배열에 값 대입
	}
	s->arr = (int*) malloc(sizeof(int)*5);	// 메모리 할당, 배열의 크기만큼 할당하기 위해 5를 곱함
	for(i = 0; i < 5; i++) {
		s->arr[i] = arr_1[i];
		printf("%d ", s->arr[i]);
	}
	system("PAUSE");
}