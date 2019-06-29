/*
	порядок вывода символов не определен
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <pthread.h>
using namespace std;

void renderChars(char c) {
	for(int i = 0; i < 150; i++) cout << c;
	cout << "\n";
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

