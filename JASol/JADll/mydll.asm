;-------------------------------------------------------------------------

.CODE

calculatePixels PROC ;BYTE* - RCX, DWORD - RDX, DWROD - R8
XOR R9, R9
XOR R10, R10
MOV R9b, 255
MOV R10b, 0
MOV RAX, RDX
MOV RBX, R8
MUL RBX
XOR RBX, RBX
BEG:
CMP RAX, RBX
JE EXT
MOV R15b, [RCX + RBX]
CMP R15b, 0
JNE SKIP1
MOV  [RCX + RBX], R9b
JMP SKIP2
SKIP1:
CMP R15b, 255
JNE SKIP2
MOV  [RCX + RBX], R10b
SKIP2:
INC RBX
JMP BEG
EXT:
RET
calculatePixels ENDP

doNothing PROC
RET
doNothing ENDP

END
;-------------------------------------------------------------------------