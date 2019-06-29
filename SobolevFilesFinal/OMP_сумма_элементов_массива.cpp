#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <omp.h>
using namespace std;

int main(int argc, char** argv) {
	// создаем массив
	int arr[30000];
	
	
	// заполняем элементы массива
	for(int i = 0; i < 30000; i++) arr[i] = (i + 17) % 9 + 1;
	
	
	// считаем сумму простым способом
	int sumSimple = 0;
	for(int i = 0; i < 30000; i++) sumSimple += arr[i];
	cout << "\n" << "Sum simple: " << sumSimple << "\n\n";
	
	
	// проверям, что OMP работает
	#pragma omp parallel 
	{
		cout << "X ";
	}
	
	
	// считаем сумму OMP
	int sumWithOMP = 0;
	#pragma omp parallel for reduction(+: sumWithOMP)
	for(int i = 0; i < 30000; i++) {
		sumWithOMP += arr[i];
	}
	cout << "\n\n" << "Sum omp: " << sumWithOMP << "\n\n";
	
	
	return 0;
}
