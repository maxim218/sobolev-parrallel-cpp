#include <iostream> 
using namespace std;

int main()
{
	// массив чисел
	alignas(16) float srcStart[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

	// вектор дл€ умножени€ кусков массива по 4 элемента на 50
	alignas(16) float vvv[4] = { 50, 50, 50, 50 };

	// массив чисел дл€ хранени€ результата
	alignas(16) float resStart[12];

	// указатель на массив
	float * src = srcStart;

	// указатель на массив дл€ хранени€ результата
	float * res = resStart;

	_asm {
		mov ecx, 0 // обнул€ем регистр дл€ счетчика

		mov eax, src // сохран€ю адрес начала массива
		mov ebx, res // сохран€ю адрес начала массива дл€ хранени€ результата

		metkaLabel: // метка дл€ цикла
			movaps xmm0, [eax] // копирование четырех чисел по адресу из EAX в регистр XMM0
			
			mulps xmm0, vvv // умножаем четыре числа в XMM0 на числа вектора vvv
			movaps [ebx], xmm0 // сохран€ем по адресу EBX четыре числа из XMM0

			add eax, 16 // сдвигаем адрес на 4 типа float
			add ebx, 16 // сдвигаем адрес на 4 типа float

			add ecx, 1 // увеличиваем счетчик
		cmp ecx, 3 // сравниваем значение счетчика с тройкой
		jne metkaLabel // если счетчик Ќ≈ равен тройке, то прыгаем на метку
	}

	for (int i = 0; i < 12; i++) {
		cout << res[i] << '\n';
	}

	cout << "\n\n\n";

	system("PAUSE");

	return 0;
}