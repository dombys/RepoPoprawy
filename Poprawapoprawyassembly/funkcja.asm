global dodaj
section .text

dodaj:
  	enter 0,0
readyoffsets:
	mov esi, [ebp + 8]
	mov edi, [ebp + 12]
	mov ecx, [ebp + 16]
add:
	add esi, ecx ;ustawienie wskaźnika tablicy 1
	add edi, ecx ;ustawienie wskaźnika tablicy 2
	mov eax, [esi]
	add eax, [edi]
done:
 	leave
  	ret
