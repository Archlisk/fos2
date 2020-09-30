%macro function 1
%1:
	push ebp
	mov ebp, esp
%endmacro

%macro return 0
	mov esp, ebp
	pop ebp
	ret
%endmacro
