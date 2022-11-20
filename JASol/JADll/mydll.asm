;-------------------------------------------------------------------------

.CODE

calculatePixels PROC			;(RCX)BYTE* - INPT_DATA_PTR, (RDX)DWORD - HEIGHT, (R8)DWROD -WIDTH, (R9)BYTE* - OTPT_DATA_PTR
;==================================================================================================================================================
XOR R10, R10					;clearing R10
XOR R11, R11					;clearing R11
XOR R12, R12					;clearing R12
XOR R13, R13					;clearing R13
XOR R14, R14					;clearing R14
XOR R15, R15					;clearing R15
;==================================================================================================================================================
MOV R12, RDX					;R12 = HEIGHT
MOV R13, R8						;R13 = WIDTH
MOV R10, 1						;R10 = I
MOV R11, 1						;R11 = J
SUB	R12, 1						;R12 = HEIGHT - 1 = END_I
SUB R13, 1						;R13 = WIDTH - 1 = END_J
;==================================================================================================================================================
BEG_LOOP_1:						;begining of LOOP_1
CMP R10, R12					;comparing I and END_I
JE EXT							;jumping exit if equal
BEG_LOOP_2:						;begining of LOOP_2
CMP R11, R13					;comparing J and END_J
JE END_LOOP_2					;jumping LOOP_2 ending if equal
XOR RAX, RAX					;clearing RAX
XOR R14, R14					;clearing R14											____
MOV RAX, R10					;RAX = I													\
SUB RAX, 1						;RAX = I - 1												\
MUL R13							;RAX = (I - 1) * WIDTH										}---> sum += _inputByteData[(i - 1) * _width + (j - 1)];
ADD RAX, R11					;RAX = (I - 1) * WIDTH + J									|
SUB RAX, 1						;RAX = (I - 1) * WIDTH + (J - 1)							|
MOV R14B, BYTE PTR [RCX + RAX]	;R14B = INPT_DATA_PTR[(I - 1) * WIDTH + (J - 1)]			|
MOV R15W, R14W					;R15W = R14W											____|
;==================================================================================================================================================
XOR RAX, RAX					;clearing RAX	
XOR R14, R14					;clearing R14											____
MOV RAX, R10					;RAX = I													\
SUB RAX, 1						;RAX = I - 1												\
MUL R13							;RAX = (I - 1) * WIDTH										}---> sum += _inputByteData[(i - 1) * _width + j];
ADD RAX, R11					;RAX = (I - 1) * WIDTH + J									|
MOV R14B, BYTE PTR [RCX + RAX]	;R14B = INPT_DATA_PTR[(I - 1) * WIDTH + J]					|
ADD R15W, R14W					;R15W += R14W											____|
;==================================================================================================================================================
XOR RAX, RAX					;clearing RAX
XOR R14, R14					;clearing R14											____
MOV RAX, R10					;RAX = I													\
SUB RAX, 1						;RAX = I - 1												\
MUL R13							;RAX = (I - 1) * WIDTH										}---> sum += _inputByteData[(i - 1) * _width + (j + 1)];
ADD RAX, R11					;RAX = (I - 1) * WIDTH + J									|
ADD RAX, 1						;RAX = (I - 1) * WIDTH + (J + 1)							|
MOV R14B, BYTE PTR [RCX + RAX]	;R14B = INPT_DATA_PTR[(I - 1) * WIDTH + (J + 1)]			|	
ADD R15W, R14W					;R15W += R14W											____|
;==================================================================================================================================================
XOR RAX, RAX					;clearing RAX
XOR R14, R14					;clearing R14											____
MOV RAX, R10					;RAX = I													\
MUL R13							;RAX = I * WIDTH											\
ADD RAX, R11					;RAX = I * WIDTH + J										}---> sum += _inputByteData[i * _width + (j - 1)
SUB RAX, 1						;RAX = I * WIDTH + (J - 1)									|
ADD R14B, BYTE PTR [RCX + RAX]	;R14B = INPT_DATA_PTR[I * WIDTH + (J - 1)]					|
ADD R15W, R14W					;R15W += R14W											____|
;==================================================================================================================================================
XOR RAX, RAX					;clearing RAX	
XOR R14, R14					;clearing R14											____
MOV RAX, R10					;RAX = I													\
MUL R13							;RAX = I * WIDTH											\
ADD RAX, R11					;RAX = I * WIDTH + J										|
MOV	R14B, BYTE PTR [RCX + RAX]	;R14B = INPT_DATA_PTR[I * WIDTH + J]						}---> sum += -2 * _inputByteData[i * _width + j];
MOV AX, R14W					;AX = INPT_DATA_PTR[I * WIDTH + J]							|
MOV R14W, -2					;R14W = -2													|
IMUL R14W						;AX = -2 * INPT_DATA_PTR[I * WIDTH + J]						|
ADD R15W, AX					;R15W += AX												____|
;==================================================================================================================================================
XOR RAX, RAX					;clearing RAX			
XOR R14, R14					;clearing R14											____
MOV RAX, R10					;RAX = I													\
MUL R13							;RAX = I * WIDTH											\
ADD RAX, R11					;RAX = I * WIDTH + J										}---> sum += _inputByteData[i * _width + (j + 1)];
ADD RAX, 1						;RAX = I * WIDTH + (J + 1)									|
MOV R14B, BYTE PTR [RCX + RAX]	;R14B = INPT_DATA_PTR[I * WIDTH + (J + 1)]					|
ADD R15W, R14W					;R15W += R14W											____|
;==================================================================================================================================================
XOR RAX, RAX					;clearing RAX	
XOR R14, R14					;clearing R14											____
MOV RAX, R10					;RAX = I													\
ADD RAX, 1						;RAX = I + 1												\
MUL R13							;RAX = (I + 1) * WIDTH										\
ADD RAX, R11					;RAX = (I + 1) * WIDTH + J									\
SUB RAX, 1						;RAX = (I + 1) * WIDTH + (J - 1)							}---> sum += -1 * _inputByteData[(i + 1) * _width + (j - 1)];
MOV R14B, BYTE PTR [RCX + RAX]	;R14B = INPT_DATA_PTR[(I + 1) * WIDTH + (J - 1)]			|
MOV AX, R14W					;AX = INPT_DATA_PTR[(I + 1) * WIDTH + (J - 1)]				|
MOV R14W, -1					;R14W = -1													|
IMUL R14W						;AX = -1 * INPT_DATA_PTR[(I + 1) * WIDTH + (J - 1)]			|
ADD R15W, AX					;R15B += AX												____|
;==================================================================================================================================================
XOR RAX, RAX					;clearing RAX	
XOR R14, R14					;clearing R14											____
MOV RAX, R10					;RAX = I													\
ADD RAX, 1						;RAX = I + 1												\
MUL R13							;RAX = (I + 1) * WIDTH										\
ADD RAX, R11					;RAX = (I + 1) * WIDTH + J									\
MOV R14B, BYTE PTR [RCX + RAX]	;R14B = INPT_DATA_PTR[(I + 1) * WIDTH + J]					}---> sum += -1 * _inputByteData[(i + 1) * _width + j];
MOV AX, R14W					;AX = INPT_DATA_PTR[(I + 1) * WIDTH + J]					|
MOV R14W, -1					;R14W = -1													|
IMUL R14W						;AX = -1 * INPT_DATA_PTR[(I + 1) * WIDTH + J]				|
ADD R15W, AX					;R15B += AX												____|
;==================================================================================================================================================
XOR RAX, RAX					;clearing RAX	
XOR R14, R14					;clearing R14											____
MOV RAX, R10					;RAX = I													\
ADD RAX, 1						;RAX = I + 1												\
MUL R13							;RAX = (I + 1) * WIDTH										\
ADD RAX, R11					;RAX = (I + 1) * WIDTH + J									\
ADD RAX, 1						;RAX = (I + 1) * WIDTH + (J + 1)							}---> sum += -1 * _inputByteData[(i + 1) * _width + (j + 1)];
MOV R14B, BYTE PTR [RCX + RAX]	;R14B = INPT_DATA_PTR[(I + 1) * WIDTH + (J + 1)]			|
MOV AX, R14W					;AX = INPT_DATA_PTR[(I + 1) * WIDTH + (J + 1)]				|
MOV R14W, -1					;R14W = -1													|
MUL R14W						;AX = -1 * INPT_DATA_PTR[(I + 1) * WIDTH + (J + 1)]			|
ADD R15W, AX					;R15B += += AX											____|
;==================================================================================================================================================
XOR RAX, RAX					;clearing RAX
XOR RBX, RBX					;clearing RBX
XOR RDX, RDX					;clearing RDX
MOV AX, R15W					;AX = R15W = SUM
MOV BX, 9						;BX = 9
DIV BX							;AX = AX / 9 = SUM / 9
MOV R15B, BL					;R15B = AL = SUM / 9
XOR RAX, RAX					;clearing RAX											____
MOV RAX, R10					;RAX = I													\
MUL R13							;RAX = I * WIDTH											\
ADD RAX, R11					;RAX = I * WIDTH + J										}---> _outputByteData[i * _width + j] = sum;
MOV BYTE PTR[R9 + RAX], R15B	;OTPT_DATA_PTR[I * WIDTH + J] = R15B					____|
;==================================================================================================================================================
INC R11							;++J
JMP BEG_LOOP_2					;jumping to begining of LOOP_2
END_LOOP_2:						;ending LOOP_2
INC R10							;++I
JMP BEG_LOOP_1					;jumping to begining of LOOP_1
EXT:							;exiting procedure
RET
calculatePixels ENDP

doNothing PROC
RET
doNothing ENDP

test1 PROC
xor rdx,rdx
xor rax,rax
xor rbx,rbx
mov ax, 500
mov bx, 181
div bx

RET
test1 ENDP

END
;-------------------------------------------------------------------------