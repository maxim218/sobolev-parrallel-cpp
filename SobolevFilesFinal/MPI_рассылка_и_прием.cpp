#include <iostream>
#include "mpi.h"
#include "windows.h"
#include <string>
#include <sstream>
using namespace std;

// мо€ функци€ дл€ получени€ строки
template <typename tip>
string toS(tip x) {
	ostringstream oss;
	oss << x;
	return oss.str();
}

int main(int argc, char * argv[]) {
	MPI_Init(&argc, &argv);

	// получить общее количество процессов
	int processesNumber;
	MPI_Comm_size(MPI_COMM_WORLD, &processesNumber);

	// получить номер текущего процесса
	int currentProcessNumber;
	MPI_Comm_rank(MPI_COMM_WORLD, &currentProcessNumber);

	// вывод информации на экран
	cout << "All: " << processesNumber << "   Current: " << currentProcessNumber << "\n";

	// если € нахожусь в нулевом процессе
	if (currentProcessNumber == 0) {
		// создаю массив размером 100 элементов
		int arr[100];
		// заполн€ю все €чейки массива
		for (int i = 0; i < 100; i++) arr[i] = i + 1;

		// пробегаюсь по номерам всех процессов (кроме нулевого)
		for (int k = 1; k < processesNumber; k++) {
			// отправл€ю заполненный массив процессу под номером "k"
			// arr - отправл€емый массив
			// 100 - размер массива
			// MPI_INTEGER - массив состоит из целых чисел
			// k - номер процесса, которому отправл€ю
			// 218 - метка
			MPI_Send(arr, 100, MPI_INTEGER, k, 218, MPI_COMM_WORLD);
		}
	} else {
		// если € нахожусь не в нулевом процессе

		// создаю массив дл€ получени€ информации от 0-го процесса
		int mass[100];
		// служебна€ переменна€ дл€ статуса передачи
		MPI_Status status;
		// принимаю заполненный массив от 0-го процесса
		// mass - куда сохран€ю полученный массив
		// 100 - размер массива
		// MPI_INTEGER - массив состоит из целых чисел
		// 0 - € принимаю сообщени€ от 0-го процесса
		// 218 - метка
		MPI_Recv(mass, 100, MPI_INTEGER, 0, 218, MPI_COMM_WORLD, &status);
		// после прин€ти€ сообщени€ от 0-го процесса формирую строку дл€ вывода на экран
		string s = "Current: " + toS(currentProcessNumber) + toS(": ");
		for (int i = 0; i < 10; i++) s = s +  toS(mass[i]) + toS(" ");
		s = s + toS("\n");
		// вывожу сформированную строку на экран
		cout << s;
	}

	MPI_Finalize();

	return 0; 
}