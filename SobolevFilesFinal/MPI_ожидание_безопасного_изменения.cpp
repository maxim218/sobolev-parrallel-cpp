#include <iostream>
#include "mpi.h"
#include "windows.h"
#include <string>
#include <sstream>
using namespace std;

/*
   mpiexec -n 5 MyProgram.exe
*/

int main(int argc, char * argv[]) {
	MPI_Init(&argc, &argv);

	// получаем общее количество процессов
	int processesNumber;
	MPI_Comm_size(MPI_COMM_WORLD, &processesNumber);

	// получаем номер текущего процесса
	int currentProcessNumber;
	MPI_Comm_rank(MPI_COMM_WORLD, &currentProcessNumber);

	// если мы в 0-м процессе
	if (currentProcessNumber == 0) {
		// выводим общее количество процессов
		cout << "Processes number: " << processesNumber << "\n";

		// массив объектов - запросов
		MPI_Request rrr[4];

		// число для отправки другим процессам
		int numberForSend = 100;
		// массив для отправки числа
		int arr[1];
		// сохраняем число в массив
		arr[0] = numberForSend;

		// пробегаемся по всем процессам
		for (int i = 0; i < processesNumber; i++) {
			// если номер процесса не ноль
			if (i != 0) {
				// асинхронно отправляем сообщение процессу под номером i
				MPI_Isend(arr, 1, MPI_INTEGER, i, 218, MPI_COMM_WORLD, &rrr[i - 1]);
			}
		}

		// массив объектов - статусов
		MPI_Status sss[4];
		// ждем возможности изменять отправляемый массив
		MPI_Waitall(4, rrr, sss);

		// уже стало безопасно изменять массив
		// изменяем массив
		arr[0] = 12345;

		// пробегаемся по всем процессам
		for (int i = 0; i < processesNumber; i++) {
			// если номер процесса не ноль
			if (i != 0) {
				// массив для получения сообщения
				int mass[1];
				// получаем сообщение
				MPI_Status status;
				MPI_Recv(mass, 1, MPI_INTEGER, i, 218, MPI_COMM_WORLD, &status);
				// выводим ответ на экран
				int value = mass[0];
				cout << "Process " << i << ": " << value << "\n";
			}
		}
	}

	// если номер процесса не ноль
	if (currentProcessNumber != 0) {
		MPI_Status status;
		// массив для получения сообщения
		int mass[1];
		// получаем сообщение
		MPI_Recv(mass, 1, MPI_INTEGER, 0, 218, MPI_COMM_WORLD, &status);
		// получаем число в сообщении
		int value = mass[0];
		// умножаем полученное значение на номер процесса
		value = value * currentProcessNumber;
		// выводим результат умножения
		cout << value << "\n";
		// массив для отправки сообщения
		int arr[1];
		arr[0] = value;
		// отправляем сообщение нулевому процессу
		MPI_Send(arr, 1, MPI_INTEGER, 0, 218, MPI_COMM_WORLD);
	}

	MPI_Finalize();

	return 0; 
}
