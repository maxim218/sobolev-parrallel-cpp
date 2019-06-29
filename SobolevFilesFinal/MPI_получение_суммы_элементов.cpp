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

	// ���� �� � 0-�� ��������
	if (currentProcessNumber == 0) {
		// ������� ������� ������
		int arr[100000];
		// ��������� ������ ����������
		for (int i = 0; i < 100000; i++) {
			arr[i] = (i + 17) % 9 + 1;
		}

		// ������ ��������� ������� ��� �������� ������ �������� �������
		int mFirst[25000];
		int mSecond[25000];
		int mThird[25000];
		int mFour[25000];

		// ������� ��� ���������� ��������� ��������
		int count;

		// �������� �������
		count = 0;
		// ��������� ������ ������
		for (int i = 0; i < 25000; i++) {
			mFirst[count] = arr[i]; 
			count++;
		}

		// �������� �������
		count = 0;
		// ��������� ������ ������
		for (int i = 25000; i < 50000; i++) {
			mSecond[count] = arr[i];
			count++;
		}

		// �������� �������
		count = 0;
		// ��������� ������ ������
		for (int i = 50000; i < 75000; i++) {
			mThird[count] = arr[i];
			count++;
		}

		// �������� �������
		count = 0;
		// ��������� ��������� ������
		for (int i = 75000; i < 100000; i++) {
			mFour[count] = arr[i];
			count++;
		}

		// ���������� 1-�� �������� ������ ������
		MPI_Send(mFirst, 25000, MPI_INTEGER, 1, 218, MPI_COMM_WORLD);
		// ���������� 2-�� �������� ������ ������
		MPI_Send(mSecond, 25000, MPI_INTEGER, 2, 218, MPI_COMM_WORLD);
		// ���������� 3-�� �������� ������ ������
		MPI_Send(mThird, 25000, MPI_INTEGER, 3, 218, MPI_COMM_WORLD);
		// ���������� 4-�� �������� ��������� ������
		MPI_Send(mFour, 25000, MPI_INTEGER, 4, 218, MPI_COMM_WORLD);

		// ���������� ��� ���������� �����
		int sss = 0;

		// ����������� �� ��������� � 1-�� �� 4-�� ������������
		for (int i = 1; i <= 4; i++) {
			// ������, � ������� ����� �������� �����, ����������� i-�� ���������
			int getArr[1];
			// ������
			MPI_Status status;
			// ���� ������ �� i-�� ��������
			MPI_Recv(getArr, 1, MPI_INTEGER, i, 220, MPI_COMM_WORLD, &status);
			// ��������� ���������� ����� � ������������� ����������
			sss = sss + getArr[0];
			// ������� ����� �� i-�� �������� �� �����
			cout << "Get from " << i << " : " << getArr[0] << "\n";
		}
		
		// ������� �� ����� ��������� (��������� �����)
		cout << "The main result of the program: " << sss << "\n";
	} else {
		// ���� �� �� � 0-�� ��������

		// ���� �� � ����� �� ��������� � 1-�� �� 4-�� ������������
		if (currentProcessNumber <= 4) {
			// ������ ��� ������ ������
			int mmm[25000];
			// ������
			MPI_Status status;
			// ��������� ������
			MPI_Recv(mmm, 25000, MPI_INTEGER, 0, 218, MPI_COMM_WORLD, &status);

			// ���������� ��� ���������� �����
			int summa = 0;
			// � ����� ������� ����� ��������� �������
			for (int i = 0; i < 25000; i++) {
				summa += mmm[i];
			}

			// ������� ���������� ����� �� �����
			cout << "Summa of process " << currentProcessNumber  << " : " << summa << "\n";

			// ������ ���������� ������� ��� �������� ���������� �����
			int ansArr[1];
			// ��������� ����� � ������
			ansArr[0] = summa;

			// ���������� ����� �������� ��������
			MPI_Send(ansArr, 1, MPI_INTEGER, 0, 220, MPI_COMM_WORLD);
		}
	}

	MPI_Finalize();

	return 0; 
}
