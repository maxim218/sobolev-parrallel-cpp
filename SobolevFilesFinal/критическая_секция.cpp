/*
	использование критической секции
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <pthread.h>
#include <conio.h>
#include "windows.h"
using namespace std;

// переменная для взаимодействия с критической секцией
CRITICAL_SECTION criticalSection;

void renderChars(char c) {
	//// 
	::EnterCriticalSection(&criticalSection); // входим в критическую секцию
	//// 
	for(int i = 0; i < 150; i++) cout << c;
	cout << "\n";
	//// 
	::LeaveCriticalSection(&criticalSection); // выходим из критической секции
	//// 
}

void * first(void *) {
	renderChars('A');
}

void * second(void *) {
	renderChars('B');
}

void * third(void *) {
	renderChars('C');
}

int main() {
	// инициализируем критическую секцию
	//// 
	::InitializeCriticalSection(&criticalSection);	
	//// 
	
	pthread_t x1, x2, x3;
	
	pthread_create(&x1, NULL, first, NULL);
	pthread_create(&x2, NULL, second, NULL);
	pthread_create(&x3, NULL, third, NULL);
	
	pthread_join(x1, NULL);
	pthread_join(x2, NULL);
	pthread_join(x3, NULL);
	
	// удаляем критическую секцию
	//// 
	::DeleteCriticalSection(&criticalSection);
	//// 
	
	cout << "\n\n";
	cout << "\n\n";
	
	return 0;
}

