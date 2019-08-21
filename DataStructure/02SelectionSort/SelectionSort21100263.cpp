/*
On my honor, I pledge that I have neither received nor provided improper
assistance in the completion of this programming assignment. Signed: Wonsik Cheung
*		Writer: Sungjin Park, Wonsik Cheung
*		Filename: SelectionSort21100263.cpp
*		Created: 2014.03.14
*		Purpose of the program:
*		How to execute: It is program to get sorted array. Users can input the amount of number.
                        Then, program sorts array after generates the amount of number users input in random. 

		Modifications: 
		1. For readability, we changed variable's name and function's name.
		2. We used memory allocation for flexibility.
		3. We seperated file(main(), SelectionSort(), CheckNumber()) for Modularization.
		4. For user-friendly interaction, we used kind and detail output messages.
		5. We improved random number generator. Now random number changes depend on time.
		6. We handled detail thing in case customer inputs charater or negative number.
*/

#include<stdio.h>
#include<math.h>
#include<Windows.h>
#include<time.h>
#include"..\include\utility.h" 

void SelectionSort(int [], int);/*selection sort*/
int CheckNumber(void);/*return the value if input string is integer number greater than zero*/

int main(void)
{
	int i; /*varible for loops */
	int customerSize; /*size inputed by customer*/
	int *numberList=NULL; /*address size for random numbers*/
	
	puts("Welcome, it is sorting program.If you enter only the size of number.");
	puts("I'll generate the amount of number you input in random(0~9999).");
	puts("Then, I'll sort that arrays. \n");

	srand((unsigned)time(NULL));/*function that change random numbers depend on time*/

	customerSize = CheckNumber();

	MALLOC(numberList, sizeof(int)*customerSize)/*memory allocation*/

	for (i = 0; i < customerSize; i++){/*randomly generate numbers*/
		numberList[i] = rand() % 10000;
		printf("%d ", numberList[i]);
	}

	SelectionSort(numberList, customerSize);

	puts("\n\nHere it is Sorted array you generate! :\n");

	for(i = 0; i < customerSize; i++)/*print out sorted numbers*/
		printf("%d ",numberList[i]);
	puts("\n");

	FREE(numberList)/*free memory*/

	system("PAUSE");
	return 0;
}

