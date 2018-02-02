	AREA text, CODE, READONLY
	EXPORT asm_math

; function Example_asm
; inputs:
; -------
; R0: input

;  MAX_INDEX S5
;  MAX_VALUE S1
;  MIN_INDEX S6
;  MIN_VALUE S2
;  RMS S3


; TMP S4
; INDEX S8

;  ARR_ELEM S4
;  ITER R7

;  INPUT R0
;  RESULT R1
;  LEN R2

asm_math
	
		;  load first element of array into MAX_VALUE and MIN_VALUE
		VLDR S1, [R0]
		VMOV.F32 S2, S1
		
		; initialize the indices
		SUB R5, R5, R5
		SUB R6, R6, R6
			
		; load the address of the first element in the register for ITER
		MOV R7, R0
			
		; R2 now holds the address of the last element
		SUB R2, R2, #1
		LSL R2, #2
		ADD R2, R2, R0
		
		; initialize S3 to first value of array
		VMOV.F32 S3, S1
		
		; initialize index to 0
		SUB R8, R8, R8
		
		; Compare address in R7 with address in R2
loop 					 
			; load contents of next array element into S4 (temp register)
			ADD R7, R7, #4
			VLDR S4, [R7]
			
			ADD R8, R8, #1
					
			; compare what's in S4 with current MAX VALUE
			VCMP.F32 S4, S1;
			VMRS APSR_nzcv, FPSCR			
			VMOVGT.F32 S1, S4
			;VMRS APSR_nzcv, FPSCR	
			ADDGT R5, R8, #0
			; VMOVGT.F32 S5, R7
			
			; compare what's in S4 with current MIN VALUE
			VCMP.F32 S4, S2;
			VMRS APSR_nzcv, FPSCR			
			VMOVLT.F32 S2, S4	
			ADDLT R6, R8, #0
			
			; square the element
			VMUL.F32 S4, S4, S4
			
			; add to total
			VADD.F32 S3, S3, S4
			
			CMP R2, R7;
			BNE loop
			
		 ; write min and max values to the array
		 
		 VSTR S1, [R1, #4]
		 VSTR S2, [R1, #8]
		 
		 ;VLDR S11, [R1, #4]
		 ;VLDR S12, [R1, #8]
		 
		 VMOV.F32 S1, R5
		 VCVT.F32.S32 S2, S1	
		 
		 VSTR S2, [R1, #12]
		 ;VLDR S13, [R1, #12]
		 
		 VMOV.F32 S1, R6
		 VCVT.F32.S32 S2, S1	
		 
		 VSTR S2, [R1, #16]
		 ;VLDR S14, [R1, #16]
		 
		 ; div S3 by R8
		 VMOV.F32 S2, R8
		 VCVT.F32.S32 S1, S2	 
		 VDIV.F32 S3, S3, S1
		 
		 ; sqare root
		 VSQRT.F32 S3, S3
		 
		 ; save rms to memory
		 VSTR S3, [R1]
		 ;VLDR S15, [R1]
		 
		 
		 ; VCVT.F32.S32 R, S6
		 ; VCVT.F32.S32 R, S5
		 ; 
		 
		 ; VMOV.F32 S2, #4.0
		 
		 ; VSUB.F32 S5, S5, S1
		 ; VDIV.F32 S5, S5, S2
		 
		 ; VSUB.F32 S6, S6, S1
		 ; VDIV.F32 S6, S6, S2
		
	END