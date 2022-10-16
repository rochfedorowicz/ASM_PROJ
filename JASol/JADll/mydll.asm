;-------------------------------------------------------------------------
.386
.MODEL FLAT, STDCALL

OPTION CASEMAP:NONE

.CODE

DllEntry PROC hInstDLL:DWORD, reason:DWORD, reserved1:DWORD

MOV	EAX, 1
RET

DllEntry ENDP

adding PROC x: DWORD, y: DWORD

XOR	EAX, EAX
MOV	EAX, x
MOV	ECX, y
ADD	EAX, ECX
RET

adding ENDP

END DllEntry
;-------------------------------------------------------------------------