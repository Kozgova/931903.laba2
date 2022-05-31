#include <iostream>

using namespace std;

void BubbleSort(int* arr, int N)
{
	int k;
	_asm {
		mov ebx, arr
		mov   edi, 0
		mov   esi, N
		
		L1_S : cmp   edi, esi
		je    L1_E

		mov   ecx, 0
		mov   edx, N
		dec   edx
		
		L2_S : cmp   ecx, edx
		je    L2_E

		mov eax, [ebx + 4 * ecx + 4]
		mov k, eax
		mov eax, [ebx + 4 * ecx]

		cmp	eax, k
		jle L3

		mov[ebx + 4 * ecx + 4], eax
		mov eax, k
		mov[ebx + 4 * ecx], eax
		L3 :
		inc   ecx
			jmp   L2_S
			L2_E :

		inc   edi
			jmp   L1_S
			L1_E :
	}
}

void GSort(int arr[], int N)
{
	int k;
	_asm {
		mov ebx, arr
		mov edx, 1

		L1_S :	cmp edx, N
		jge L1_E

		mov eax, [ebx + 4 * edx]
		mov k, eax
		mov eax, [ebx + 4 * edx - 4]

		cmp   eax, k
		jg    L2_S
		inc edx
		jmp   L2_E
		L2_S :
		mov[ebx + 4 * edx], eax
			mov eax, k
			mov[ebx + 4 * edx - 4], eax

			cmp edx, 1
			jle L3
			dec	edx
			L3 :
	L2_E:
		jmp L1_S
			L1_E :
	}
}

int main()
{
	int Sort[10] = { 18, 22, 0, 3, 1, 6, 6, 11, -4, 8 };
	int Sort2[10] = { 18, 22, 0, 3, 1, 6, 6, 11, -4, 8 };
	int* p1 = Sort, * p2 = Sort2;

	std::cout << "Before any Sort:" << std::endl;
	for (int i = 0; i < 10; i++)
	{
		std::cout << Sort[i] << std::endl;
	}

	_asm {
		push 10
		push p1
		call BubbleSort
		pop eax
		pop eax
	}

	_asm {
		push 10
		push p2
		call GSort
		pop eax
		pop eax
	}

	std::cout << "After BubbleSort:" << std::endl;
	for (int i = 0; i < 10; i++)
	{
		std::cout << Sort[i] << std::endl;
	}

	std::cout << "After GSort:" << std::endl;
	for (int i = 0; i < 10; i++)
	{
		std::cout << Sort2[i] << std::endl;
	}
}