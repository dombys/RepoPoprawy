global dodaj
section .text

dodaj:
  	enter 0,0
readyoffsets:
	mov eax, [ebp+8] ;wskazanie na 1. tablice
	mov esi, eax ;offset tablicy 1.
	mov eax, [ebp + 12] ;wskazanie na 2. tablice
	mov edi, eax
	mov eax, [ebp + 16] ;element tablicy
	mov ecx, eax
add:
	add esi, ecx ;ustawienie wskaźnika tablicy 1
	add edi, ecx ;ustawienie wskaźnika tablicy 2
	mov eax, [esi]
	add eax, [edi]
done:
 	leave
  	ret
