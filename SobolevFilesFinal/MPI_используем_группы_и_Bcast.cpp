#include <iostream>
#include "mpi.h"
#include "windows.h"
#include <string>
#include <sstream>
using namespace std;

/*
   mpiexec -n 8 MyProgram.exe
*/

// ��� ������� ��� ��������� ������
template <typename tip>
string toS(tip x) {
	ostringstream oss;
	oss << x;
	return oss.str();
}

int main(int argc, char * argv[]) {
	MPI_Init(&argc, &argv);

	// �������� ����� ���������� ���������
	int processesNumber;
	MPI_Comm_size(MPI_COMM_WORLD, &processesNumber);

	// �������� ����� �������� ��������
	int currentProcessNumber;
	MPI_Comm_rank(MPI_COMM_WORLD, &currentProcessNumber);

	// ������� ������� ������
	MPI_Group baseGroup;
	MPI_Comm_group(MPI_COMM_WORLD, &baseGroup);

	// ������� ��������� ��� ������ ������
	int membersGroupFirst[4];
	// ������� ��������� ��� ������ ������
	int membersGroupSecond[4];

	// ������ ������� ��������� ������ ������ (������ ������)
	membersGroupFirst[0] = 0;
	membersGroupFirst[1] = 2;
	membersGroupFirst[2] = 4;
	membersGroupFirst[3] = 6;

	// ������ ������� ��������� ������ ������ (�������� ������)
	membersGroupSecond[0] = 1;
	membersGroupSecond[1] = 3;
	membersGroupSecond[2] = 5;
	membersGroupSecond[3] = 7;


	// ������ - ������ ������
	MPI_Group groupFirst;
	// ������ - ������ ������
	MPI_Group groupSecond;

	// ������� ������ ������ �� ������ ������� �������� ��������� ��� ������ ������
	MPI_Group_incl(baseGroup, 4, membersGroupFirst, &groupFirst);
	// ������� ������ ������ �� ������ ������� �������� ��������� ��� ������ ������
	MPI_Group_incl(baseGroup, 4, membersGroupSecond, &groupSecond);

	// ������������ ��� ������ ������
	MPI_Comm commFirst;
	// ������������ ��� ������ ������
	MPI_Comm commSecond;

	// ������� ������������ ��� ������ ������
	MPI_Comm_create(MPI_COMM_WORLD, groupFirst, &commFirst);
	// ������� ������������ ��� ������ ������
	MPI_Comm_create(MPI_COMM_WORLD, groupSecond, &commSecond);

	// ���� ������������� ��� ������ ������ ��� � �������
	if (commFirst == MPI_COMM_NULL) {
		// ����� ��������� �� ���������� ������� �������� � ������� �������������
		string s = toS("From process ") + toS(currentProcessNumber) + toS(": comm First is NULL \n");
		cout << s;
	}

	// ���� ������������� ��� ������ ������ ��� � �������
	if (commSecond == MPI_COMM_NULL) {
		// ����� ��������� �� ���������� ������� �������� �� ������� �������������
		string s = toS("From process ") + toS(currentProcessNumber) + toS(": comm Second is NULL \n");
		cout << s;
	}

	// ���� ����� �������� ��������� � ������ ������
	if (currentProcessNumber % 2 == 0) {
		// ������� ������
		int arrFirst[10];
		// ���� �� ������ � ������� ��������
		if (currentProcessNumber == 0) {
			// ��������� ������ ������ � ������� ��������
			for (int i = 0; i < 10; i++) arrFirst[i] = 111;
		}
		// ��������� ������ ���� ��������� ������ ������
		// ����� �������� ������ ����� ��������������� � ���� ��������� ������ ������
		MPI_Bcast(arrFirst, 10, MPI_INTEGER, 0, commFirst);
		// ��������� ��������� ��� ������ ������� �� �����
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
