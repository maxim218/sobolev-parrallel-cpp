/*
	���������� �������
*/

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

// ���������� ��� ������ � ���������
sem_t sem;

void renderChars(char c) {
	////
	sem_wait(&sem); // ���������
	////
	for(int i = 0; i < 150; i++) cout << c;
	cout << "\n";
	////
	sem_post(&sem); // ���������
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
	// ������ ���� ����� � ����������� ������ ������� ����� ��������� ���
	sem_init(&sem, 0, 1); 
	
	pthread_t x1, x2, x3;
	
	pthread_create(&x1, NULL, first, NULL);
	pthread_create(&x2, NULL, second, NULL);
	pthread_create(&x3, NULL, third, NULL);
	
	pthread_join(x1, NULL);
	pthread_join(x2, NULL);
	pthread_join(x3, NULL);
	
	// ������� �������
	sem_destroy(&sem);
	
	cout << "\n\n";
	cout << "\n\n";
	
	return 0;
}

