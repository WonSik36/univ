#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int CheckNumber(void){
	int n;/*varible for loop*/
	char numberAmount[15];/*string to get size of customerSize*/

	for(n=0;n<15;n++)/*initialize variables in numberAmount*/
		numberAmount[n]=-1;
	n=0;

	while(1){ /*loop to get integer number up to 14-digit-number*/
		fputs("Enter the number you want to generate. : ",stdout);
		gets(numberAmount);

		while(n<15 && (numberAmount[n]!=-1)){
			if(isdigit(numberAmount[n])){
				n++;
				continue;
			}
			else if(numberAmount[n]==0)
				return atoi(numberAmount);

			else{
				puts("\nSorry, I can't process the number you entered, ");
				puts("Please enter integer number greater than zero. \n");
				return CheckNumber();
			}
		}
	}
}