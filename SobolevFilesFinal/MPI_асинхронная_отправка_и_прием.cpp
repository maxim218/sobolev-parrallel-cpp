#include <iostream>
#include "mpi.h"
#include "windows.h"
#include <string>
#include <sstream>
using namespace std;

/*
   mpiexec -n 2 MyProgram.exe
*/

int main(int argc, char * argv[]) {
	MPI_Init(&argc, &argv);

	// получаем общее количество процессов
	int processesNumber;
	MPI_Comm_size(MPI_COMM_WORLD, &processesNumber);

	// получаем номер текущего процесса
	int currentProcessNumber;
	MPI_Comm_rank(MPI_COMM_WORLD, &currentProcessNumber);

	if (currentProcessNumber == 0) {
		// создаем массив и заполняем его значениями 3000
		int arr[100];
		for (int i = 0; i < 100; i++) arr[i] = 3000;

		// отправляем асинхронное сообщение на 1-ый процесс
		MPI_Request request;
		MPI_Isend(arr, 100, MPI_INTEGER, 1, 218, MPI_COMM_WORLD, &request);

		/*
			здесь можно что-нибудь делать
			при этом здесь нельзя работать с массивом "arr"
		*/

		// ждем момента, когда можно будет безопасно взаимодействовать с массивом "arr"
		MPI_Status status;
		MPI_Wait(&request, &status);

		// изменяем ячейки массива "arr"
		// при этом мы ничего не испортим в 1-ом процессе
		arr[1] = 15;
		arr[3] = 35;
		arr[5] = 55;
		arr[7] = 75;
	}

	if (currentProcessNumber == 1) {
		// массив для сохранения содержимого сообщения
		int mass[100];

		// асинхронно получаем сообщение
		MPI_Request request;
		MPI_Irecv(mass, 100, MPI_INTEGER, 0, 218, MPI_COMM_WORLD, &request);

		/*
			что - нибудь делаем
			при этом "mass" использовать нельзя
		*/

		// ждем момента, когда будет можно безопасно взаимодействовать с "mass"
		MPI_Status status;
		MPI_Wait(&request, &status);

		// выводим кусок массива "mass" в консоль
		for (int i = 0; i < 9; i++) cout << i << ")  " << mass[i] << "\n";
		cout << "\n";
	}

	MPI_Finalize();

	return 0; 
}
