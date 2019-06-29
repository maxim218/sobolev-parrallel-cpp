#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <omp.h>
#include <string>
#include <sstream>
using namespace std;

// �������������� � ������
template <typename tip>
string toS(tip x) {
	ostringstream oss;
	oss << x;
	return oss.str();
}

int main(int argc, char** argv) {
	// ���������� ����� 1 ��� ��� �������� ������
	cout << "\n\n" << "Start program" << "\n\n";

	// ���������� ��� ������� ������
	#pragma omp parallel
	{
		// ���������� ����� ������
		int num = omp_get_thread_num();

		// �������� ����������� ��������� ���������
		string message = toS("Thread: ") + toS(num);

		// � ����������� �� ������ ������ ��������� ������� ���������

		if (num == 1) {
			message = message + toS("  First \n");
		}
		else if (num == 2) {
			message = message + toS("  Second \n");
		}
		else if (num == 3) {
			message = message + toS("  Third \n");
		}
		else {
			message = message + toS(" \n");
		}

		// ������� ��������� �� �����
		cout << message;
	}

	// ���������� ����� 1 ��� ��� �������� ������
	cout << "\n\n";

	system("PAUSE");
	return 0;
}

