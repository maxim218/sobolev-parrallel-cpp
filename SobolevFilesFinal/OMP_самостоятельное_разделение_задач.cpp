#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <omp.h>
#include <string>
#include <sstream>
using namespace std;

// преобразование в строку
template <typename tip>
string toS(tip x) {
	ostringstream oss;
	oss << x;
	return oss.str();
}

int main(int argc, char** argv) {
	// выполнится ровно 1 раз для главного потока
	cout << "\n\n" << "Start program" << "\n\n";

	// выполнится для каждого потока
	#pragma omp parallel
	{
		// определяем номер потока
		int num = omp_get_thread_num();

		// начинаем формировать текстовое сообщение
		string message = toS("Thread: ") + toS(num);

		// в зависимости от номера потока формируем контент сообщения

		if (num == 1) {
			message = message + toS("  First \n");
		}
		else if (num == 2) {
			message = message + toS("  Second \n");
		}
		else if (num == 3) {
			message = message + toS("  Third \n");
		}
		else {
			message = message + toS(" \n");
		}

		// выводим сообщение на экран
		cout << message;
	}

	// выполнится ровно 1 раз для главного потока
	cout << "\n\n";

	system("PAUSE");
	return 0;
}

