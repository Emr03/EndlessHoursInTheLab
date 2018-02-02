#include <stdio.h>
#include <stdlib.h>
#include "arm_math.h"
#include <float.h>


void FIR_C(int *Input, float32_t *Output, int length);
void asm_math(float32_t* Output, float32_t* Result, int length);

void CMSIS_math(float32_t *Input, float32_t *Result, uint32_t Length){
	float32_t CMSIS_RMS;
	
	arm_rms_f32(&Input[0], Length, &CMSIS_RMS);
	printf("%f \n", CMSIS_RMS); 
	
	float32_t max; 
	uint32_t max_index; 
	arm_max_f32(&Input[0], Length, &max, &max_index);
	printf("%f \n", max); 
	
	float32_t min; 
	uint32_t min_index; 
	arm_min_f32(&Input[0], Length, &min, &min_index);
	printf("%f \n", min); 
	
	Result[0] = CMSIS_RMS; 
	Result[1] = max; 
	Result[2] = min; 
	Result[3] = max_index; 
	Result[4] = min_index; 
	
}

void C_math(float32_t *Input, float32_t *Output, int Length){
	
	//max,maxIndex,min,minIndex,rms
	//float math[5] = {0, 0, 0, 0, 0};
	
	//FIR_C(&Input[0], Output, Length);
	
	Output[2] = Input[0];
	Output[0] = Input[0];
	
	for (int i=1; i<Length; i++){
		Output[4] += Input[i]*Input[i];
		//Output[4] += pow(Input[i],2.0);
		if (Input[i] > Output[0]){
			printf("%s %f \n", "max : ", Input[i]);
			Output[0] = Input[i];
			Output[1] = i;
		}
		else if(Input[i] < Output[2]){
			printf("%s %f \n", "min : ", Input[i]);
			Output[2] = Input[i];
			Output[3] = i;
		}

	}
	
	Output[4] /= Length;
	Output[4] = sqrt(Output[4]);
}

#define VAR

void FIR_C(int *Input, float32_t *Output, int length){

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
	srand(9);
	int Input_3[100]; 
	for (int k=0; k<100; k++){
		Input_3[k] = rand()%10;
	}
	float32_t *Output = (float32_t*) malloc(100*sizeof(float32_t));  
	
	FIR_C(&Input_3[0], Output, 10);
	
	float32_t* Result = (float32_t*) malloc(5*sizeof(Input_3[0]));
	//C math test cases
	float math[5] = {0, 0, 0, 0, 0};
	//C_math(Output, math, 10);
	
	for(int i=0; i<10; i++){
		printf("%f \n", Output[i]);
	}
	
	printf("%p \n", Result);
	
	asm_math(Output, Result, 100); 
		

	printf("%f \n", Result[0]);
	printf("%f \n", Result[1]);
	printf("%f \n", Result[2]);
	printf("%f \n", Result[3]);
	printf("%f \n", Result[4]);
	
	
	printf("%s \n", "*******************************");
	/*
	for(int i=0; i<5; i++){
		printf("%f \n", Result[i]); 
	}*/

	/*
	C_math(Output, Result, 100); 
	
	printf("%f \n", Result[0]);
	printf("%f \n", Result[1]);
	printf("%f \n", Result[2]);
	printf("%f \n", Result[3]);
	printf("%f \n", Result[4]);
	*/
	printf("%s \n", "*******************************");
	/*
	float32_t* Result_1 = (float32_t*) malloc(5*sizeof(float32_t));
	CMSIS_math(Output, Result_1, 100);
	
	printf("%f \n", Result_1[0]);
	printf("%f \n", Result_1[1]);
	printf("%f \n", Result_1[2]);
	printf("%f \n", Result_1[3]);
	printf("%f \n", Result_1[4]);
	*/
	return 0;
}
