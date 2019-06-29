/*
	������ � ����������
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <pthread.h>
#include <mutex>
using namespace std;

// ������ ��� ������ � ���������
mutex myMutex;

void renderChars(char c) {
	/////
	myMutex.lock(); // �����������
	/////
	for(int i = 0; i < 150; i++) cout << c;
	cout << "\n";
	/////
	myMutex.unlock(); // ��������������
	/////
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
	pthread_t x1, x2, x3;
	
	pthread_create(&x1, NULL, first, NULL);
	pthread_create(&x2, NULL, second, NULL);
	pthread_create(&x3, NULL, third, NULL);
	
	pthread_join(x1, NULL);
	pthread_join(x2, NULL);
	pthread_join(x3, NULL);
	
	cout << "\n\n";
	cout << "\n\n";
	
	return 0;
}

