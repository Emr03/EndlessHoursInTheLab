#include <stdio.h>
#include <stdlib.h>
#include "arm_math.h"

void FIR_C(int* Input, float* Output){
	int N = 4;
	
	int length = sizeof(*Input) / sizeof(Input[0]);
	printf("%d", length); 

	float B[5] = {0.1, 0.15, 0.5, 0.15, 0.1};
	
	Output = (float*) malloc(sizeof(*Input));  
	
	// hard coded for first 4
	// Output[0] = B[0]*Input[0];
	// Output[1] = B[0]*Input[1] + B[1]*Input[0]; 
	// Output[2] = B[0]*Input[2] + B[1]*Input[1] + B[2]*Input[0];
	// Output[3] = B[0]*Input[3] + B[1]*Input[2] + B[2]*Input[1] + B[3]*Input[0];
	
	//for (int i = length-1; i >= 0; i--){
	//	*Input = *Input >> (32);
	//	Output[i] = B[0]*Input[length-1] + B[1]*Input[length-2] + B[2]*Input[length-3] + B[3]*Input[length-4] + B[4]*Input[length-5];
	//}
	
	for (int i = 0; i < length; i++){
		Output[i] = 0;
		for (int j=0; j<N; j++){
			if (!((i-j) < 0)) {
				printf("%s \n", "Yo");
				Output[i] += B[j]*Input[i-j];
			}
	}
}
	
}

int main()
{
	
	// basic tests for naive implementation
	int Input[1] = {0};
	printf("%s \n", "Executing Test 1...");
	float* Output;
	*Output = -1; 	
	FIR_C(Input, Output);
	printf("%f \n", Output[0]);
	 
	printf("%s \n", "Executing Test 2...");	
	int Input_2[6] = {0, 0, 0, 0, 0, 0};
	*Output = -1; 
	FIR_C(Input_2, Output);
	printf("%f \n", Output[0]);
	
	printf("%s \n", "Executing Test 3...");	
	int Input_3[10] = {1, 2, 1, 2, 3, -1, -2, -3, 1, 1}; 
	*Output = -1; 
	FIR_C(Input_3, Output);
	printf("%f \n", Output[0]);

	
	return 0;
}
