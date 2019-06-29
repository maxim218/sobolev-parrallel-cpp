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

	// �������� ����� ���������� ���������
	int processesNumber;
	MPI_Comm_size(MPI_COMM_WORLD, &processesNumber);

	// �������� ����� �������� ��������
	int currentProcessNumber;
	MPI_Comm_rank(MPI_COMM_WORLD, &currentProcessNumber);

	// ���� �� � 0-� ��������
	if (currentProcessNumber == 0) {
		// ������� ����� ���������� ���������
		cout << "Processes number: " << processesNumber << "\n";

		// ������ �������� - ��������
		MPI_Request rrr[4];

		// ����� ��� �������� ������ ���������
		int numberForSend = 100;
		// ������ ��� �������� �����
		int arr[1];
		// ��������� ����� � ������
		arr[0] = numberForSend;

		// ����������� �� ���� ���������
		for (int i = 0; i < processesNumber; i++) {
			// ���� ����� �������� �� ����
			if (i != 0) {
				// ���������� ���������� ��������� �������� ��� ������� i
				MPI_Isend(arr, 1, MPI_INTEGER, i, 218, MPI_COMM_WORLD, &rrr[i - 1]);
			}
		}

		// ������ �������� - ��������
		MPI_Status sss[4];
		// ���� ����������� �������� ������������ ������
		MPI_Waitall(4, rrr, sss);

		// ��� ����� ��������� �������� ������
		// �������� ������
		arr[0] = 12345;

		// ����������� �� ���� ���������
		for (int i = 0; i < processesNumber; i++) {
			// ���� ����� �������� �� ����
			if (i != 0) {
				// ������ ��� ��������� ���������
				int mass[1];
				// �������� ���������
				MPI_Status status;
				MPI_Recv(mass, 1, MPI_INTEGER, i, 218, MPI_COMM_WORLD, &status);
				// ������� ����� �� �����
				int value = mass[0];
				cout << "Process " << i << ": " << value << "\n";
			}
		}
	}

	// ���� ����� �������� �� ����
	if (currentProcessNumber != 0) {
		MPI_Status status;
		// ������ ��� ��������� ���������
		int mass[1];
		// �������� ���������
		MPI_Recv(mass, 1, MPI_INTEGER, 0, 218, MPI_COMM_WORLD, &status);
		// �������� ����� � ���������
		int value = mass[0];
		// �������� ���������� �������� �� ����� ��������
		value = value * currentProcessNumber;
		// ������� ��������� ���������
		cout << value << "\n";
		// ������ ��� �������� ���������
		int arr[1];
		arr[0] = value;
		// ���������� ��������� �������� ��������
		MPI_Send(arr, 1, MPI_INTEGER, 0, 218, MPI_COMM_WORLD);
	}

	MPI_Finalize();

	return 0; 
}
