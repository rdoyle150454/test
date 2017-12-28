#include <stdio.h>
#include <stdlib.h>
#include "func.h"

void error_exit(){ 
	printf("Invalid input. Exiting.");
	exit(1);
}

 int main()
 {
  int num1, num2, addTot, subTot, multiTot;
  
  printf("Enter the first number: ");
	if(!scanf("%d", &num1)){
		error_exit();
	}
	
 printf("\nEnter the second number: ");
	if(!scanf("%d", &num2)){
		error_exit();
	}
 
  addTot = add(num1, num2);	
  printf("\nAddition: %d\n",addTot);
  subTot = subtract(num1, num2);
  printf("\nSubtraction: %d\n",subTot);
  multiTot = multiply(num1, num2);	
  addTot = add(num1, num2);
  printf("\nMultiply: %d\n",multiTot);	
  return 0;
 }
