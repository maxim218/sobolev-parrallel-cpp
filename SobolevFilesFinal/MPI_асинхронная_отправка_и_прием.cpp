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

	// �������� ����� ���������� ���������
	int processesNumber;
	MPI_Comm_size(MPI_COMM_WORLD, &processesNumber);

	// �������� ����� �������� ��������
	int currentProcessNumber;
	MPI_Comm_rank(MPI_COMM_WORLD, &currentProcessNumber);

	if (currentProcessNumber == 0) {
		// ������� ������ � ��������� ��� ���������� 3000
		int arr[100];
		for (int i = 0; i < 100; i++) arr[i] = 3000;

		// ���������� ����������� ��������� �� 1-�� �������
		MPI_Request request;
		MPI_Isend(arr, 100, MPI_INTEGER, 1, 218, MPI_COMM_WORLD, &request);

		/*
			����� ����� ���-������ ������
			��� ���� ����� ������ �������� � �������� "arr"
		*/

		// ���� �������, ����� ����� ����� ��������� ����������������� � �������� "arr"
		MPI_Status status;
		MPI_Wait(&request, &status);

		// �������� ������ ������� "arr"
		// ��� ���� �� ������ �� �������� � 1-�� ��������
		arr[1] = 15;
		arr[3] = 35;
		arr[5] = 55;
		arr[7] = 75;
	}

	if (currentProcessNumber == 1) {
		// ������ ��� ���������� ����������� ���������
		int mass[100];

		// ���������� �������� ���������
		MPI_Request request;
		MPI_Irecv(mass, 100, MPI_INTEGER, 0, 218, MPI_COMM_WORLD, &request);

		/*
			��� - ������ ������
			��� ���� "mass" ������������ ������
		*/

		// ���� �������, ����� ����� ����� ��������� ����������������� � "mass"
		MPI_Status status;
		MPI_Wait(&request, &status);

		// ������� ����� ������� "mass" � �������
		for (int i = 0; i < 9; i++) cout << i << ")  " << mass[i] << "\n";
		cout << "\n";
	}

	MPI_Finalize();

	return 0; 
}
