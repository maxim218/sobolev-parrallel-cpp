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

	// если мы в 0-ом процессе
	if (currentProcessNumber == 0) {
		// создаем большой массив
		int arr[100000];
		// заполняем массив значениями
		for (int i = 0; i < 100000; i++) {
			arr[i] = (i + 17) % 9 + 1;
		}

		// четыре маленьких массива для хранения кусков большого массива
		int mFirst[25000];
		int mSecond[25000];
		int mThird[25000];
		int mFour[25000];

		// счетчик для заполнения маленьких массивов
		int count;

		// обнуляем счетчик
		count = 0;
		// заполняем первый массив
		for (int i = 0; i < 25000; i++) {
			mFirst[count] = arr[i]; 
			count++;
		}

		// обнуляем счетчик
		count = 0;
		// заполняем второй массив
		for (int i = 25000; i < 50000; i++) {
			mSecond[count] = arr[i];
			count++;
		}

		// обнуляем счетчик
		count = 0;
		// заполняем третий массив
		for (int i = 50000; i < 75000; i++) {
			mThird[count] = arr[i];
			count++;
		}

		// обнуляем счетчик
		count = 0;
		// заполняем четвертый массив
		for (int i = 75000; i < 100000; i++) {
			mFour[count] = arr[i];
			count++;
		}

		// отправляем 1-му процессу первый массив
		MPI_Send(mFirst, 25000, MPI_INTEGER, 1, 218, MPI_COMM_WORLD);
		// отправляем 2-му процессу второй массив
		MPI_Send(mSecond, 25000, MPI_INTEGER, 2, 218, MPI_COMM_WORLD);
		// отправляем 3-му процессу третий массив
		MPI_Send(mThird, 25000, MPI_INTEGER, 3, 218, MPI_COMM_WORLD);
		// отправляем 4-му процессу четвертый массив
		MPI_Send(mFour, 25000, MPI_INTEGER, 4, 218, MPI_COMM_WORLD);

		// переменная для накопления суммы
		int sss = 0;

		// пробегаемся по процессам с 1-го по 4-ый включительно
		for (int i = 1; i <= 4; i++) {
			// массив, в который будет записана сумма, посчитанная i-ым процессом
			int getArr[1];
			// статус
			MPI_Status status;
			// ждем ответа от i-го процесса
			MPI_Recv(getArr, 1, MPI_INTEGER, i, 220, MPI_COMM_WORLD, &status);
			// добавляем полученную сумму к накопительной переменной
			sss = sss + getArr[0];
			// выводим ответ от i-го процесса на экран
			cout << "Get from " << i << " : " << getArr[0] << "\n";
		}
		
		// выводим на экран результат (финальную сумму)
		cout << "The main result of the program: " << sss << "\n";
	} else {
		// если мы не в 0-ом процессе

		// если мы в одном из процессов с 1-го по 4-ый включительно
		if (currentProcessNumber <= 4) {
			// массив для приема данных
			int mmm[25000];
			// статус
			MPI_Status status;
			// принимаем массив
			MPI_Recv(mmm, 25000, MPI_INTEGER, 0, 218, MPI_COMM_WORLD, &status);

			// переменная для сохранения суммы
			int summa = 0;
			// в цикле считаем сумму элементов массива
			for (int i = 0; i < 25000; i++) {
				summa += mmm[i];
			}

			// выводим полученную сумму на экран
			cout << "Summa of process " << currentProcessNumber  << " : " << summa << "\n";

			// массив единичного размера для отправки полученной суммы
			int ansArr[1];
			// сохраняем сумму в массив
			ansArr[0] = summa;

			// отправляем сумму нулевому процессу
			MPI_Send(ansArr, 1, MPI_INTEGER, 0, 220, MPI_COMM_WORLD);
		}
	}

	MPI_Finalize();

	return 0; 
}
