#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <omp.h>
using namespace std;

int getSumSimple(int * arr) {
	// считаем сумму простым способом
	int sumSimple = 0;
	for (int i = 0; i < 30000; i++) sumSimple += arr[i];
	return sumSimple;
}

int getSumWithOMP(int * arr) {
	// считаем сумму OMP
	int sumWithOMP = 0;
	#pragma omp parallel for reduction(+: sumWithOMP)
	for (int i = 0; i < 30000; i++) {
		sumWithOMP += arr[i];
	}
	return sumWithOMP;
}

int main(int argc, char** argv) {
	// создаем массив
	int arr[30000];


	// заполняем элементы массива
	for (int i = 0; i < 30000; i++) arr[i] = (i + 17) % 9 + 1;

	for (int test = 0; test < 10; test++) {
		double startSimple = omp_get_wtime();
		int s1 = 0;
		for (int i = 0; i < 9999; i++) {
			s1 = getSumSimple(arr);
		}
		double stopSimple = omp_get_wtime();
		cout << "Simple: " << s1 << "  Time: " << (stopSimple - startSimple) << "\n";
	}

	cout << "\n";

	// проверям, что OMP работает
	#pragma omp parallel 
	{
		cout << "X ";
	}

	cout << "\n\n";

	for (int test = 0; test < 10; test++) {
		double startOMP = omp_get_wtime();
		int s2 = 0;
		for (int i = 0; i < 9999; i++) {
			s2 = getSumWithOMP(arr);
		}
		double stopOMP = omp_get_wtime();
		cout << "OMP: " << s2 << "  Time: " << (stopOMP - startOMP) << "\n";
	}

	cout << "\n\n";

	system("PAUSE");
	return 0;
}
