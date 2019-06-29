#include <iostream>
#include "mpi.h"
#include "windows.h"
#include <string>
#include <sstream>
using namespace std;

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

	// ����� ���������� �� �����
	cout << "All: " << processesNumber << "   Current: " << currentProcessNumber << "\n";

	// ���� � �������� � ������� ��������
	if (currentProcessNumber == 0) {
		// ������ ������ �������� 100 ���������
		int arr[100];
		// �������� ��� ������ �������
		for (int i = 0; i < 100; i++) arr[i] = i + 1;

		// ���������� �� ������� ���� ��������� (����� ��������)
		for (int k = 1; k < processesNumber; k++) {
			// ��������� ����������� ������ �������� ��� ������� "k"
			// arr - ������������ ������
			// 100 - ������ �������
			// MPI_INTEGER - ������ ������� �� ����� �����
			// k - ����� ��������, �������� ���������
			// 218 - �����
			MPI_Send(arr, 100, MPI_INTEGER, k, 218, MPI_COMM_WORLD);
		}
	} else {
		// ���� � �������� �� � ������� ��������

		// ������ ������ ��� ��������� ���������� �� 0-�� ��������
		int mass[100];
		// ��������� ���������� ��� ������� ��������
		MPI_Status status;
		// �������� ����������� ������ �� 0-�� ��������
		// mass - ���� �������� ���������� ������
		// 100 - ������ �������
		// MPI_INTEGER - ������ ������� �� ����� �����
		// 0 - � �������� ��������� �� 0-�� ��������
		// 218 - �����
		MPI_Recv(mass, 100, MPI_INTEGER, 0, 218, MPI_COMM_WORLD, &status);
		// ����� �������� ��������� �� 0-�� �������� �������� ������ ��� ������ �� �����
		string s = "Current: " + toS(currentProcessNumber) + toS(": ");
		for (int i = 0; i < 10; i++) s = s +  toS(mass[i]) + toS(" ");
		s = s + toS("\n");
		// ������ �������������� ������ �� �����
		cout << s;
	}

	MPI_Finalize();

	return 0; 
}