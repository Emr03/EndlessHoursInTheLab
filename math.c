#include <stdlib.h>
#include <float.h>
#include <math.h>

void FIR_C(int *Input, float *Output, int index){

	float B[5] = {0.2, 0.2, 0.2, 0.2, 0.2};
	
	switch(index){
		case(0):
			Output[0] = Input[0]*B[0];
			break;
		case(1):
			Output[1] = B[0]*Input[1] + B[1]*Input[0];
			break;
		case(2):
			Output[2] = B[0]*Input[2] + B[1]*Input[1] + B[2]*Input[0];
			break;
		case(3):
			Output[3] = B[0]*Input[3] + B[1]*Input[2] + B[2]*Input[1] + B[3]*Input[0];
			break;
		default:
			Output[index] = B[0]*Input[index] + B[1]*Input[index-1] + B[2]*Input[index-2] + B[3]*Input[index-3] + B[4]*Input[index-4];
	}

}


void C_math(float *Input, float *Output, int Length){
	
	//max,maxIndex,min,minIndex,rms (return array)
	
	//initialize min and max to first element of the array
	Output[2] = Input[0];
	Output[0] = Input[0];
	
	//initialize minIndex and maxIndex to 0
	Output[1] = 0;
	Output[3] = 0;
	
	for (int i=1; i<Length; i++){
		//
		Output[4] += Input[i]*Input[i];
		//check input[i] to see if it's greater than current max
		if (Input[i] > Output[0]){
			Output[0] = Input[i];
			Output[1] = i;
		}
		//check input[i] to see if it's less than current min
		else if(Input[i] < Output[2]){
			Output[2] = Input[i];
			Output[3] = i;
		}

	}
	
	Output[4] /= Length;
	Output[4] = sqrt(Output[4]);
}



