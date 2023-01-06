;====================================================================================================================================================================
;====================================================================================================================================================================
;====================================================================================================================================================================
.DATA
W DQ ?		
EN_J DQ ?
EN_C DQ 3
DIV_9 DQ 2097865012304223517
SHFT DQ 8
;====================================================================================================================================================================
;====================================================================================================================================================================
.CODE

calculatePixels PROC			;(RCX)BYTE* - INPT_DATA_PTR, (RDX)DWORD - HEIGHT, (R8)DWROD -WIDTH, (R9)BYTE* - OTPT_DATA_PTR
PUSH RAX						;save current RAX value
PUSH RBX						;save current RBX value
PUSH RCX						;save current RCX value
PUSH RDX						;save current RDX value
PUSH RBP						;save current RBP value
PUSH RDI						;save current RDI value
PUSH RSI						;save current RSI value
PUSH R8							;save current R8 value
PUSH R9							;save current R9 value
PUSH R10						;save current R10 value
PUSH R11						;save current R11 value
PUSH R12						;save current R12 value
PUSH R13						;save current R13 value
PUSH R14						;save current R14 value
PUSH R15						;save current R15 value
MOV W, R8						;W = WIDTH
MOV	R13, RCX					;R13 = INPT_DATA_PTR
SUB	RDX, 1						;RDX = HEIGHT - 1 = END_I
SUB R8, 1						;R8 = WIDTH - 1
MOV RAX, R8						;RAX = WIDTH - 1
MOV R8, RDX						;EN_I = END_I
XOR RBX, RBX					;clearing RBX
XOR RCX, RCX					;clearing RCX
XOR RDX, RDX					;clearing RDX
MOV R15, 3						;R15 = 3
DIV R15							;RAX = RAX / 3 = (WIDTH - 1) / 3
SUB RAX, 1						;RAX = RAX / 3 - 1 = (WIDTH - 1) / 3 - 1 = END_J
XOR R15, R15					;clearing R15
XOR RDX, RDX					;clearing RDX
MOV	EN_J, RAX					;EN_J = END_J
XOR R10, R10					;clearing R10
MOV R10, 1						;R10 = I
XOR R11, R11					;clearing R11
MOV R11, 1						;R11 = J
XOR R12, R12					;clearing R12
MOV R12, 0						;R12 = CHANNEL_NR
;====================================================================================================================================================================
BEG_LOOP_1:						;begining of LOOP_1
CMP R10, R8						;comparing I and END_I
JE EXT							;jumping exit if equal
BEG_LOOP_2:						;begining of LOOP_2
CMP R11, EN_J					;comparing J and END_J
JE END_LOOP_2					;jumping LOOP_2 ending if equal
BEG_LOOP_3:						;begining of LOOP_3
CMP R12, EN_C					;comparing CHANNEL and END_C
JE END_LOOP_3					;jumping LOOP_3 ending if equal
;====================================================================================================================================================================				
MOV RAX, R10					;RAX = I														----\
SUB RAX, 1						;RAX = I - 1														\
MUL W							;RAX = (I - 1) * WIDTH												\
MOV R14, R11					;R14 = J															\
SUB R14, 1						;R14 = J - 1														\
LEA	R14, [2 * R14 + R14]		;R14 = (J - 1) * 3													\
ADD R14, R12					;R14 = (J - 1) * 3 + CHANNEL_NR										}---> sum += _inputByteData[(i - 1) * _width + (j - 1) * 3 + channel];
ADD RAX, R14					;RAX = (I - 1) * WIDTH + (J - 1) * 3 + CHANNEL_NR					|
MOV RBX, R13					;RBX = INPT_DATA_PTR												|
XOR R14, R14					;clearing R14														|
MOV R14B, BYTE PTR [RBX + RAX]	;R14B = INPT_DATA_PTR[(I - 1) * WIDTH + (J - 1) * 3 + CHANNEL_NR]	|
MOV R15W, R14W					;R15W = R14W													----|
;====================================================================================================================================================================
MOV RAX, R10					;RAX = I														----\
SUB RAX, 1						;RAX = I - 1														\
MUL W							;RAX = (I - 1) * WIDTH												\
MOV R14, R11					;R14 = J															\
LEA R14, [2 * R14 + R14]		;R14 = J * 3														\
ADD R14, R12					;R14 = J * 3 + CHANNEL_NR											}---> sum += _inputByteData[(i - 1) * _width + j * 3 + channel];
ADD RAX, R14					;RAX = (I - 1) * WIDTH + J * 3 + CHANNEL_NR							|
MOV RBX, R13					;RBX = INPT_DATA_PTR												|
XOR R14, r14					;clearing R14														|
MOV R14B, BYTE PTR [RBX + RAX]	;R14B = INPT_DATA_PTR[(I - 1) * WIDTH + J * 3 + CHANNEL_NR]			|
ADD R15W, R14W					;R15W += R14W													----|
;====================================================================================================================================================================
MOV RAX, R10					;RAX = I														----\
SUB RAX, 1						;RAX = I - 1														\
MUL W							;RAX = (I - 1) * WIDTH												\
MOV R14, R11					;R14 = J															\
ADD R14, 1						;R14 = J + 1														\
LEA	R14, [2 * R14 + R14]		;R14 = (J + 1) * 3													\
ADD R14, R12					;R14 = (J + 1) * 3 + CHANNEL_NR										}---> sum += _inputByteData[(i - 1) * _width + (j + 1) * 3 + channel];
ADD RAX, R14					;RAX = (I - 1) * WIDTH + (J + 1) * 3 + CHANNEL_NR					|
MOV RBX, R13					;RBX = INPT_DATA_PTR												|
XOR R14, R14					;clearing R14														|
MOV R14B, BYTE PTR [RBX + RAX]	;R14B = INPT_DATA_PTR[(I - 1) * WIDTH + (J + 1) * 3 + CHANNEL_NR]	|
ADD R15W, R14W					;R15W += R14W													----|
;====================================================================================================================================================================
MOV RAX, R10					;RAX = I														----\
MUL W							;RAX = I * WIDTH													\
MOV R14, R11					;R14 = J															\
SUB R14, 1						;R14 = J - 1														\
LEA	R14, [2 * R14 + R14]		;R14 = (J - 1) * 3													\
ADD R14, R12					;R14 = (J - 1) * 3 + CHANNEL_NR										}---> sum += _inputByteData[i * _width + (j - 1) * 3 + channel];
ADD RAX, R14					;RAX = I * WIDTH + (J - 1) * 3 + CHANNEL_NR							|
MOV RBX, R13					;RBX = INPT_DATA_PTR												|
XOR R14, R14					;clearing R14														|
MOV R14B, BYTE PTR [RBX + RAX]	;R14B = INPT_DATA_PTR[I * WIDTH + (J - 1) * 3 + CHANNEL_NR]			|
ADD R15W, R14W					;R15W += R14W													----|
;====================================================================================================================================================================								____
MOV RAX, R10					;RAX = I														----\
MUL W							;RAX = I * WIDTH													\
MOV R14, R11					;R14 = J															\
LEA R14, [2 * R14 + R14]		;R14 = J * 3														\
ADD R14, R12					;R14 = J * 3 + CHANNEL_NR											\
ADD RAX, R14					;RAX = I * WIDTH + J * 3 + CHANNEL_NR								\
MOV RBX, R13					;RBX = INPT_DATA_PTR												}---> sum += -2 * _inputByteData[i * _width + j * 3 + channel];
XOR R14, R14					;clearing R14														|
MOV	R14B, BYTE PTR [RBX + RAX]	;R14B = INPT_DATA_PTR[I * WIDTH + J * 3 + CHANNEL_NR]				|
XOR RAX, RAX					;clearing RAX														|
MOV AX, R14W					;AX = INPT_DATA_PTR[I * WIDTH + J * 3 + CHANNEL_NR]					|
MOV R14W, -2					;R14W = -2															|
IMUL R14W						;AX = -2 * INPT_DATA_PTR[I * WIDTH + J * 3 + CHANNEL_NR]			|
ADD R15W, AX					;R15W += AX														----|
;====================================================================================================================================================================
MOV RAX, R10					;RAX = I														----\
MUL W							;RAX = I * WIDTH													\
MOV R14, R11					;R14 = J															\
ADD R14, 1						;R14 = J + 1														\
LEA	R14, [2 * R14 + R14]		;R14 = (J + 1) * 3													\
ADD R14, R12					;R14 = (J + 1) * 3 + CHANNEL_NR										}---> sum += _inputByteData[i * _width + (j + 1) * 3 + channel];
ADD RAX, R14					;RAX = I * WIDTH + (J + 1) * 3 + CHANNEL_NR							|
MOV RBX, R13					;RBX = INPT_DATA_PTR												|
XOR R14, R14					;clearing R14														|
MOV R14B, BYTE PTR [RBX + RAX]	;R14B = INPT_DATA_PTR[I * WIDTH + (J + 1) * 3 + CHANNEL_NR]			|
ADD R15W, R14W					;R15W += R14W													----|
;====================================================================================================================================================================
MOV RAX, R10					;RAX = I														----\
ADD RAX, 1						;RAX = I + 1														\
MUL W							;RAX = (I + 1) * WIDTH												\
MOV R14, R11					;R14 = J															\
SUB R14, 1						;R14 = J - 1														\
LEA R14, [2 * R14 + R14]		;R14 = (J - 1) * 3													\
ADD R14, R12					;R14 = (J - 1) * 3 + CHANNEL_NR										\
ADD RAX, R14					;RAX = (I + 1) * WIDTH + (J - 1) * 3 + CHANNEL_NR					\
MOV RBX, R13					;RBX = INPT_DATA_PTR												}---> sum += -1 * _inputByteData[(i + 1) * _width + (j - 1) * 3 + channel];
XOR R14, R14					;clearing R14														|
MOV	R14B, BYTE PTR [RBX + RAX]	;R14B = INPT_DATA_PTR[(I + 1) * WIDTH + (J - 1) * 3 + CHANNEL_NR]	|
XOR RAX, RAX					;clearing RAX														|
MOV AX, R14W					;AX = INPT_DATA_PTR[(I + 1) * WIDTH + (J - 1) * 3 + CHANNEL_NR]		|
MOV R14W, -1					;R14W = -1															|
IMUL R14W						;AX = -1 * INPT_DATA_PTR[(I + 1) * WIDTH + (J - 1) * 3 + CHANNEL_NR]|
ADD R15W, AX					;R15W += AX														----|
;====================================================================================================================================================================
MOV RAX, R10					;RAX = I														----\
ADD RAX, 1						;RAX = I + 1														\
MUL W							;RAX = (I + 1) * WIDTH												\
MOV R14, R11					;R14 = J															\
LEA R14, [2 * R14 + R14]		;R14 = J * 3														\
ADD R14, R12					;R14 = J * 3 + CHANNEL_NR											\
ADD RAX, R14					;RAX = (I + 1) * WIDTH + J * 3 + CHANNEL_NR							\
MOV RBX, R13					;RBX = INPT_DATA_PTR												}---> sum += -1 * _inputByteData[(i + 1) * _width + j * 3 + channel];
XOR R14, R14					;clearing R14														|
MOV	R14B, BYTE PTR [RBX + RAX]	;R14B = INPT_DATA_PTR[(I + 1) * WIDTH + J * 3 + CHANNEL_NR]			|
XOR RAX, RAX					;clearing RAX														|
MOV AX, R14W					;AX = INPT_DATA_PTR[(I + 1) * WIDTH + J * 3 + CHANNEL_NR]			|
MOV R14W, -1					;R14W = -1															|
IMUL R14W						;AX = -1 * INPT_DATA_PTR[(I + 1) * WIDTH + J * 3 + CHANNEL_NR]		|
ADD R15W, AX					;R15W += AX														----|
;====================================================================================================================================================================
MOV RAX, R10					;RAX = I														----\
ADD RAX, 1						;RAX = I + 1														\
MUL W							;RAX = (I + 1) * WIDTH												\
MOV R14, R11					;R14 = J															\
ADD R14, 1						;R14 = J + 1														\
LEA R14, [2 * R14 + R14]		;R14 = (J + 1) * 3													\
ADD R14, R12					;R14 = (J + 1) * 3 + CHANNEL_NR										\
ADD RAX, R14					;RAX = (I + 1) * WIDTH + (J + 1) * 3 + CHANNEL_NR					\
MOV RBX, R13					;RBX = INPT_DATA_PTR												}---> sum += -1 * _inputByteData[(i + 1) * _width + (j + 1) * 3 + channel];
XOR R14, R14					;clearing R14														|
MOV	R14B, BYTE PTR [RBX + RAX]	;R14B = INPT_DATA_PTR[(I + 1) * WIDTH + (J + 1) * 3 + CHANNEL_NR]	|
XOR RAX, RAX					;clearing RAX														|
MOV AX, R14W					;AX = INPT_DATA_PTR[(I + 1) * WIDTH + (J + 1) * 3 + CHANNEL_NR]		|
MOV R14W, -1					;R14W = -1															|
IMUL R14W						;AX = -1 * INPT_DATA_PTR[(I + 1) * WIDTH + (J + 1) * 3 + CHANNEL_NR]|
ADD R15W, AX					;R15W += AX														----|
;====================================================================================================================================================================
CMP R15W, 0						;comparing R15W to 0											----\
JNS SKIP						;skipping for positive												\
MOV R15W, 0						;R15W = 0, when it is negative										\
SKIP:							;skipped for positive												\
XOR RAX, RAX					;clearing RAX														\
MOV AX, R15W					;AX = R15W = SUM													\
XOR RBX, RBX					;clearing RBX														\
XOR RDX, RDX					;clearing RDX														\
MOV BX, 9						;BX = 9																\
DIV BX							;AX = AX / 9 = SUM / 9												\
XOR R15, R15					;clearing R15														}---> _outputByteData[i * _width + j * 3 + channel] = sum / 9 < 0 ? 0 : sum / 9;
MOV R15B, AL					;R15B = AL = SUM / 9												|
MOV RAX, R10					;RAX = I															|
MUL W							;RAX = I * WIDTH													|
MOV R14, R11					;R14 = J 															|
LEA R14, [2 * R14 + R14]		;R14 = J * 3														|
ADD R14, R12					;R14 = J * 3 + CHANNEL_NR											|
ADD RAX, R14					;RAX = I *  + J * 3 + CHANNEL_NR									|
MOV RBX, R9						;RBX = OTPT_DATA_PTR												|
MOV BYTE PTR[RBX + RAX], R15B	;OTPT_DATA_PTR[I *  + J * 3 + CHANNEL_NR] = R15B				----|
;====================================================================================================================================================================
INC R12							;++CHANNEL
JMP BEG_LOOP_3					;jumping to begining of LOOP_3
END_LOOP_3:						;ending LOOP_3
INC R11							;++J
MOV R12, 0						;R12 = CHANNEL_NR = 0
JMP BEG_LOOP_2					;jumping to begining of LOOP_2
END_LOOP_2:						;ending LOOP_2
INC R10							;++I
MOV R11, 1						;R11 = J = 1
JMP BEG_LOOP_1					;jumping to begining of LOOP_1
EXT:							;exiting procedure
POP R15							;restore current R15 value
POP R14							;restore current R14 value
POP R13							;restore current R13 value
POP R12							;restore current R12 value
POP R11							;restore current R11 value
POP R10							;restore current R10 value
POP R9							;restore current R9	value
POP R8							;restore current R8	value
POP RSI							;restore current RSI value
POP RDI							;restore current RDI value
POP RBP							;restore current RBP value
POP RDX							;restore current RDX value
POP RCX							;restore current RCX value
POP RBX							;restore current RBX value
POP RAX							;restore current RAX value
RET
calculatePixels ENDP
;====================================================================================================================================================================
;====================================================================================================================================================================
calculatePixelsWithVI PROC		;(RCX)BYTE* - INPT_DATA_PTR, (RDX)DWORD - HEIGHT, (R8)DWROD -WIDTH, (R9)BYTE* - OTPT_DATA_PTR
PUSH RAX						;save current RAX value
PUSH RBX						;save current RBX value
PUSH RCX						;save current RCX value
PUSH RDX						;save current RDX value
PUSH RBP						;save current RBP value
PUSH RDI						;save current RDI value
PUSH RSI						;save current RSI value
PUSH R8							;save current R8 value
PUSH R9							;save current R9 value
PUSH R10						;save current R10 value
PUSH R11						;save current R11 value
PUSH R12						;save current R12 value
PUSH R13						;save current R13 value
PUSH R14						;save current R14 value
PUSH R15						;save current R15 value
;====================================================================================================================================================================
MOV W, R8						;W = WIDTH
MOV	R13, RCX					;R13 = INPT_DATA_PTR
SUB	RDX, 1						;RDX = HEIGHT - 1 = END_I
MOV R8, RDX						;EN_I = END_I
MOV RAX, W						;RAX = WIDTH
SUB RAX, 1						;RAX = WIDTH - 1
SHR RAX, 3						;RAX = (WIDTH - 1) / 8 = END_J
MOV	EN_J, RAX					;EN_J = END_J
MOV R10, 1						;R10 = I
MOV R11, 1						;R11 = J
;====================================================================================================================================================================
MOV RCX, W						;RCX = WIDTH
LEA RAX, [R10 - 1]				;RAX = I - 1												
MUL RCX							;RAX = (I - 1) * WIDTH											
LEA R14, [R11 - 1]				;R14 = J - 1													
LEA	R14, [2 * R14 + R14]		;R14 = (J - 1) * 3												
ADD R14, R12					;R14 = (J - 1) * 3 + CHANNEL_NR									
ADD RAX, R14					;RAX = (I - 1) * WIDTH + (J - 1) * 3 + CHANNEL_NR
;====================================================================================================================================================================
MOVQ XMM10, DIV_9
PUNPCKLBW XMM10, XMM0
MOVQ XMM11, SHFT
;====================================================================================================================================================================
BEG_LOOP_1:						;begining of LOOP_1
CMP R10, R8						;comparing I and END_I
JE EXT							;jumping exit if equal
BEG_LOOP_2:						;begining of LOOP_2
CMP R11, EN_J					;comparing J and END_J
JE END_LOOP_2					;jumping LOOP_2 ending if equal
;====================================================================================================================================================================
PXOR XMM0, XMM0
MOVQ XMM1, QWORD PTR [R13 + RAX]	
PUNPCKLBW XMM1, XMM0				
;====================================================================================================================================================================	
ADD RAX, 3						
MOVQ XMM2, QWORD PTR [R13 + RAX]	
PUNPCKLBW XMM2, XMM0														
;====================================================================================================================================================================
ADD RAX, 3						
MOVQ XMM3, QWORD PTR [R13 + RAX]	
PUNPCKLBW XMM3, XMM0												
;====================================================================================================================================================================
LEA RAX, [RAX + RCX - 6]		
MOVQ XMM4, QWORD PTR [R13 + RAX]	
PUNPCKLBW XMM4, XMM0	
;====================================================================================================================================================================								____
ADD RAX, 3
MOVQ XMM5, QWORD PTR [R13 + RAX]			
PUNPCKLBW XMM5, XMM0		
;====================================================================================================================================================================
ADD RAX, 3						
MOVQ XMM6, QWORD PTR [R13 + RAX]
PUNPCKLBW XMM6, XMM0												
;====================================================================================================================================================================		
LEA RAX, [RAX + RCX - 6]
MOVQ XMM7, QWORD PTR [R13 + RAX]			
PUNPCKLBW XMM7, XMM0	
;====================================================================================================================================================================
ADD RAX, 3
MOVQ XMM8, QWORD PTR [R13 + RAX]			
PUNPCKLBW XMM8, XMM0	
;====================================================================================================================================================================
ADD RAX, 3
MOVQ XMM9, QWORD PTR [R13 + RAX]			
PUNPCKLBW XMM9, XMM0	
;====================================================================================================================================================================
PADDUSW XMM1, XMM2
PADDUSW XMM1, XMM3
PADDUSW XMM1, XMM4
PADDUSW XMM1, XMM6
PSUBUSW XMM1, XMM5
PSUBUSW XMM1, XMM5
PSUBUSW XMM1, XMM7
PSUBUSW XMM1, XMM8
PSUBUSW XMM1, XMM9
;====================================================================================================================================================================
PMULLW XMM1, XMM10
PSRAW XMM1, XMM11
PACKUSWB XMM1, XMM0
SUB RAX, W						;RAX = I * WIDTH + (J + 1) * 3 + CHANNEL_NR
SUB RAX, 3						;RAX = I * WIDTH + J * 3 + CHANNEL_NR
MOVQ QWORD PTR[R9 + RAX], XMM1	;OTPT_DATA_PTR[I * WIDTH + J * 3 + CHANNEL_NR] = R15B				
;====================================================================================================================================================================
SUB RAX, W						;RAX = (I - 1) * WIDTH + J * 3 + CHANNEL_NR
ADD RAX, 5						;RAX = (I - 1) * WIDTH + (J - 1) * 3 + CHANNEL_NR_NEXT
INC R11							;++J
JMP BEG_LOOP_2					;jumping to begining of LOOP_2
END_LOOP_2:						;ending LOOP_2
MOV RBX, EN_J
SHL RBX, 3
SUB RAX, RBX
ADD RAX, W
ADD RAX, 8
INC R10							;++I
MOV R11, 1						;R11 = J = 1
JMP BEG_LOOP_1					;jumping to begining of LOOP_1
;====================================================================================================================================================================
EXT:							;exiting procedure
POP R15							;restore current R15 value
POP R14							;restore current R14 value
POP R13							;restore current R13 value
POP R12							;restore current R12 value
POP R11							;restore current R11 value
POP R10							;restore current R10 value
POP R9							;restore current R9	value
POP R8							;restore current R8	value
POP RSI							;restore current RSI value
POP RDI							;restore current RDI value
POP RBP							;restore current RBP value
POP RDX							;restore current RDX value
POP RCX							;restore current RCX value
POP RBX							;restore current RBX value
POP RAX							;restore current RAX value
RET
calculatePixelsWithVI ENDP

END
;====================================================================================================================================================================
;====================================================================================================================================================================
;====================================================================================================================================================================