#include <stdio.h>
#include <stdlib.h>
#include "arm_math.h"


#define VAR

void FIR_C(int *Input, float *Output, int length){

	float B[5] = {0.1, 0.15, 0.5, 0.15, 0.1};
	
	#ifdef VAR
	// hard coded for first 4
	*Output = B[0]*Input[0];
	*(Output +1) = B[0]*Input[1] + B[1]*Input[0]; 
	Output[2] = B[0]*Input[2] + B[1]*Input[1] + B[2]*Input[0];
	Output[3] = B[0]*Input[3] + B[1]*Input[2] + B[2]*Input[1] + B[3]*Input[0];
	
	for (int i = 4; i <length; i++){
		Output[i] = B[0]*Input[i] + B[1]*Input[i-1] + B[2]*Input[i-2] + B[3]*Input[i-3] + B[4]*Input[i-4];
	}
	#endif
	
	#ifndef VAR
	int N = 4;
	printf("%s \n", "executing"); 
	for (int i = 0; i < length; i++){
		Output[i] = 0;
		for (int j=0; j<N; j++){
			if (!((i-j) < 0)) {
				printf("%s \n", "Yo");
				Output[i] += B[j]*Input[i-j];
			}
	}
}
	#endif
	
}

int main()
{
	
	// basic tests for naive implementation
	int Input[1] = {0};
	printf("%s \n", "Executing Test 1...");
	float *Output; 
	Output = (float*) malloc(10*sizeof(Input[0]));
	FIR_C(&Input[0], Output, 1);
	printf("%f \n", Output[0]);
	 
	printf("%s \n", "Executing Test 2...");	
	int Input_2[6] = {0, 0, 0, 0, 0, 0};
	Output = (float*) malloc(10*sizeof(Input_2[0]));
	FIR_C(&Input_2[0], Output, 6);
	printf("%f \n", Output[0]);
	
	printf("%s \n", "Executing Test 3...");	
	int Input_3[10] = {1, 2, 1, 2, 3, -1, -2, -3, 1, 1}; 
	Output = (float*) malloc(10*sizeof(Input_3[0]));  
	FIR_C(&Input_3[0], Output, 10);
	printf("%f \n", Output[0]);

	
	return 0;
}
