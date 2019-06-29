#include <iostream>
#include "mpi.h"
#include "windows.h"
#include <string>
#include <sstream>
using namespace std;

/*
   mpiexec -n 8 MyProgram.exe
*/

// моя функция для получения строки
template <typename tip>
string toS(tip x) {
	ostringstream oss;
	oss << x;
	return oss.str();
}

int main(int argc, char * argv[]) {
	MPI_Init(&argc, &argv);

	// получаем общее количество процессов
	int processesNumber;
	MPI_Comm_size(MPI_COMM_WORLD, &processesNumber);

	// получаем номер текущего процесса
	int currentProcessNumber;
	MPI_Comm_rank(MPI_COMM_WORLD, &currentProcessNumber);

	// создаем базовую группу
	MPI_Group baseGroup;
	MPI_Comm_group(MPI_COMM_WORLD, &baseGroup);

	// индексы процессов для первой группы
	int membersGroupFirst[4];
	// индексы процессов для второй группы
	int membersGroupSecond[4];

	// задаем индексы процессов первой группы (четные номера)
	membersGroupFirst[0] = 0;
	membersGroupFirst[1] = 2;
	membersGroupFirst[2] = 4;
	membersGroupFirst[3] = 6;

	// задаем индексы процессов второй группы (нечетные номера)
	membersGroupSecond[0] = 1;
	membersGroupSecond[1] = 3;
	membersGroupSecond[2] = 5;
	membersGroupSecond[3] = 7;


	// объект - первая группа
	MPI_Group groupFirst;
	// объект - вторая группа
	MPI_Group groupSecond;

	// создаем первую группу на основе массива индексов процессов для первой группы
	MPI_Group_incl(baseGroup, 4, membersGroupFirst, &groupFirst);
	// создаем вторую группу на основе массива индексов процессов для второй группы
	MPI_Group_incl(baseGroup, 4, membersGroupSecond, &groupSecond);

	// коммуникатор для первой группы
	MPI_Comm commFirst;
	// коммуникатор для второй группы
	MPI_Comm commSecond;

	// создаем коммуникатор для первой группы
	MPI_Comm_create(MPI_COMM_WORLD, groupFirst, &commFirst);
	// создаем коммуникатор для второй группы
	MPI_Comm_create(MPI_COMM_WORLD, groupSecond, &commSecond);

	// если коммуникатора для первой группы НЕТ в доступе
	if (commFirst == MPI_COMM_NULL) {
		// вывод сообщения об отсутствии доступа процесса к первому коммуникатору
		string s = toS("From process ") + toS(currentProcessNumber) + toS(": comm First is NULL \n");
		cout << s;
	}

	// если коммуникатора для второй группы НЕТ в доступе
	if (commSecond == MPI_COMM_NULL) {
		// вывод сообщения об отсутствии доступа процесса ко второму коммуникатору
		string s = toS("From process ") + toS(currentProcessNumber) + toS(": comm Second is NULL \n");
		cout << s;
	}

	// если номер процесса находится в первой группе
	if (currentProcessNumber % 2 == 0) {
		// создаем массив
		int arrFirst[10];
		// если мы именно в нулевом процессе
		if (currentProcessNumber == 0) {
			// заполняем массив ТОЛЬКО В НУЛЕВОМ ПРОЦЕССЕ
			for (int i = 0; i < 10; i++) arrFirst[i] = 111;
		}
		// рассылаем массив всем процессам первой группы
		// после рассылки массив будет инициализирован у всех процессов первой группы
		MPI_Bcast(arrFirst, 10, MPI_INTEGER, 0, commFirst);
		// формируем сообщение для вывода массива на экран
		string s = toS("Data message of process ") + toS(currentProcessNumber) + toS(": ");
		for (int i = 0; i < 10; i++) s = s + toS(arrFirst[i]) + toS(" ");
		s = s + toS("\n");
		cout << s;
	}

	if (currentProcessNumber % 2 == 1) {
		int arrSecond[10];
		if (currentProcessNumber == 1) {
			for (int i = 0; i < 10; i++) arrSecond[i] = 222;
		}
		MPI_Bcast(arrSecond, 10, MPI_INTEGER, 0, commSecond);
		string s = toS("Data message of process ") + toS(currentProcessNumber) + toS(": ");
		for (int i = 0; i < 10; i++) s = s + toS(arrSecond[i]) + toS(" ");
		s = s + toS("\n");
		cout << s;
	}

	MPI_Finalize();

	return 0;
}
