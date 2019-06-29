#include <iostream>
#include "mpi.h"
using namespace std;

int main(int argc, char * argv[])
{
	MPI_Init(&argc, &argv);

	// �������� ����� ���������� ���������
	int processesNumber;
	MPI_Comm_size(MPI_COMM_WORLD, &processesNumber);

	// �������� ����� �������� ��������
	int currentProcessNumber;
	MPI_Comm_rank(MPI_COMM_WORLD, &currentProcessNumber);

	// ����� ���������� �� �����
	cout << "All: " << processesNumber << "   Current: " << currentProcessNumber << "\n";

	MPI_Finalize();

	return 0; 
}

