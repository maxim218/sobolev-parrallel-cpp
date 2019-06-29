#include <iostream> 
using namespace std;

int main()
{
	// ������ �����
	alignas(16) float srcStart[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

	// ������ ��� ��������� ������ ������� �� 4 �������� �� 50
	alignas(16) float vvv[4] = { 50, 50, 50, 50 };

	// ������ ����� ��� �������� ����������
	alignas(16) float resStart[12];

	// ��������� �� ������
	float * src = srcStart;

	// ��������� �� ������ ��� �������� ����������
	float * res = resStart;

	_asm {
		mov ecx, 0 // �������� ������� ��� ��������

		mov eax, src // �������� ����� ������ �������
		mov ebx, res // �������� ����� ������ ������� ��� �������� ����������

		metkaLabel: // ����� ��� �����
			movaps xmm0, [eax] // ����������� ������� ����� �� ������ �� EAX � ������� XMM0
			
			mulps xmm0, vvv // �������� ������ ����� � XMM0 �� ����� ������� vvv
			movaps [ebx], xmm0 // ��������� �� ������ EBX ������ ����� �� XMM0

			add eax, 16 // �������� ����� �� 4 ���� float
			add ebx, 16 // �������� ����� �� 4 ���� float

			add ecx, 1 // ����������� �������
		cmp ecx, 3 // ���������� �������� �������� � �������
		jne metkaLabel // ���� ������� �� ����� ������, �� ������� �� �����
	}

	for (int i = 0; i < 12; i++) {
		cout << res[i] << '\n';
	}

	cout << "\n\n\n";

	system("PAUSE");

	return 0;
}