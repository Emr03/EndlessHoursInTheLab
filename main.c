#include <stdio.h>
#include <stdlib.h>
#include "arm_math.h"
#include <float.h>


void FIR_C(int *Input, float *Output, int length);
void asm_math(float* Output, float* Result, int length);


void C_math(float *Input, float *Output, int Length){
	
	//max,maxIndex,min,minIndex,rms
	//float math[5] = {0, 0, 0, 0, 0};
	
	//FIR_C(&Input[0], Output, Length);
	
	Output[2] = FLT_MAX;
	Output[0] = FLT_MIN;
	
	for (int i=0; i<Length; i++){
		Output[4] += Input[i]*Input[i];
		//Output[4] += pow(Input[i],2.0);
		if (Input[i] > Output[0]){
			printf("%s %d \n", "max : ", Input[i]);
			Output[0] = Input[i];
			Output[1] = i;
		}
		if(Input[i] < Output[2]){
			printf("%s %d \n", "min : ", Input[i]);
			Output[2] = Input[i];
			Output[3] = i;
		}

	}
	
	Output[4] /= Length;
	Output[4] = sqrt(Output[4]);
}

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

	printf("%s \n", "Executing Test 3...");	
	int Input_3[10] = {1, 2, 1, 2, 3, -1, -2, -3, 1, 1}; 
	float *Output = (float*) malloc(10*sizeof(Input_3[0]));  
	
	FIR_C(&Input_3[0], Output, 10);
	
	float* Result = (float*) malloc(10*sizeof(Input_3[0]));
	//C math test cases
	float math[5] = {0, 0, 0, 0, 0};
	//C_math(Output, math, 10);
	
	for(int i=0; i<10; i++){
		printf("%f \n", Output[i]);
	}
	
	asm_math(Output, Result, 10); 

	

	
	return 0;
}
