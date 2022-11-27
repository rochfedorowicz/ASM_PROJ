;====================================================================================================================================================================
;====================================================================================================================================================================
;====================================================================================================================================================================
.DATA
H DQ ?
W DQ ?
IDP DQ ?
ODP DQ ?
EN_I DQ ?					
EN_J DQ ?
EN_C DQ 3
;====================================================================================================================================================================
;====================================================================================================================================================================
.CODE
calculatePixels PROC			;(RCX)BYTE* - INPT_DATA_PTR, (RDX)DWORD - HEIGHT, (R8)DWROD -WIDTH, (R9)BYTE* - OTPT_DATA_PTR
MOV H, RDX						;H = HEIGHT
MOV W, R8						;W = WIDTH
MOV IDP, RCX					;IDP = INPT_DATA_PTR
MOV ODP, R9						;ODP = OTPT_DATA_PTR
SUB	RDX, 1						;RDX = HEIGHT - 1 = END_I
MOV EN_I, RDX					;EN_I = END_I
SUB R8, 1						;R8 = WIDTH - 1
MOV RAX, R8						;RAX = WIDTH - 1
XOR RBX, RBX					;clearing RBX
XOR RCX, RCX					;clearing RCX
XOR RDX, RDX					;clearing RDX
MOV R15, 3						;R15 = 3
DIV R15							;RAX = RAX / 3 = (WIDTH - 1) / 3 = END_J
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
CMP R10, EN_I					;comparing I and END_I
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
MOV RBX, IDP					;RBX = INPT_DATA_PTR												|
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
MOV RBX, IDP					;RBX = INPT_DATA_PTR												|
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
MOV RBX, IDP					;RBX = INPT_DATA_PTR												|
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
MOV RBX, IDP					;RBX = INPT_DATA_PTR												|
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
MOV RBX, IDP					;RBX = INPT_DATA_PTR												}---> sum += -2 * _inputByteData[i * _width + j * 3 + channel];
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
MOV RBX, IDP					;RBX = INPT_DATA_PTR												|
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
MOV RBX, IDP					;RBX = INPT_DATA_PTR												}---> sum += -1 * _inputByteData[(i + 1) * _width + (j - 1) * 3 + channel];
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
MOV RBX, IDP					;RBX = INPT_DATA_PTR												}---> sum += -1 * _inputByteData[(i + 1) * _width + j * 3 + channel];
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
MOV RBX, IDP					;RBX = INPT_DATA_PTR												}---> sum += -1 * _inputByteData[(i + 1) * _width + (j + 1) * 3 + channel];
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
MOV RBX, ODP					;RBX = OTPT_DATA_PTR												|
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
RET
calculatePixels ENDP
;====================================================================================================================================================================
;====================================================================================================================================================================
doNothing PROC
RET
doNothing ENDP
;====================================================================================================================================================================
;====================================================================================================================================================================
test1 PROC
RET
test1 ENDP
END
;====================================================================================================================================================================
;====================================================================================================================================================================
;====================================================================================================================================================================