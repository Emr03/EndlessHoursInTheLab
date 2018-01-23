#include <stdio.h>
#include <stdlib.h>
#include "arm_math.h"

void FIR_C(int* Input, float* Output){
	
	int length = sizeof(*Input) / sizeof(Input[0]);
	float B[5] = {0.1, 0.15, 0.5, 0.15, 0.1};
	
	Output = (float*) malloc(sizeof(*Input));  
	
	// hard coded for first 4
	Output[0] = B[0]*Input[0];
	Output[1] = B[0]*Input[1] + B[1]*Input[0]; 
	Output[2] = B[0]*Input[2] + B[1]*Input[1] + B[2]*Input[0];
	Output[3] = B[0]*Input[3] + B[1]*Input[2] + B[2]*Input[1] + B[3]*Input[0];
	
	for (int i = 4; i < length; i++){
		Output[i] = B[0]*Input[i] + B[1]*Input[i-1] + B[2]*Input[i-2] + B[3]*Input[i-3] + B[4]*Input[i-4];
	}
}

int main()
{
	
	// basic tests for naive implementation
	int Input[1] = {0};
	printf("%s", "test 1");
	float* Output;
	*Output = -1; 	
	FIR_C(Input, Output);
	printf("%s", Output[0]);
	 
		
	int Input_2[6] = {0, 0, 0, 0, 0, 0};
	*Output = -1; 
	FIR_C(Input_2, Output);
	
	int Input_3[10] = {1, 2, 1, 2, 3, -1, -2, -3, 1, 1}; 
	*Output = -1; 
	FIR_C(Input_3, Output);

	
	return 0;
}
