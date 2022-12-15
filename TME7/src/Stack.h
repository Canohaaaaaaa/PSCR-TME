#pragma once

#include <cstring> // size_t,memset
#include <semaphore.h>
#include <fcntl.h>
#include <iostream>
using namespace std;
namespace pr {

#define STACKSIZE 100

template<typename T>
class Stack {
	T tab [STACKSIZE];
	size_t sz;
	sem_t semaphore_full;
	sem_t semaphore_empty;
	sem_t mutex;
public :
	Stack () : sz(0) { 
		memset(tab,0,sizeof tab);
		sem_init(&semaphore_full, 1, STACKSIZE);
		sem_init(&semaphore_empty, 1, 0);
		sem_init(&mutex, 1, 1);
	}
	~Stack() {
		sem_destroy(&semaphore_full);
		sem_destroy(&semaphore_empty);
		sem_destroy(&mutex);
	}

	T pop () {
		sem_wait(&semaphore_empty);
		sem_wait(&mutex);
		cout << "popped !" << endl;
		T toret = tab[--sz];
		sem_post(&semaphore_full);
		sem_post(&mutex);
		return toret;
	}

	void push(T elt) {
		sem_wait(&semaphore_full);
		sem_wait(&mutex);
		cout << "pushed !" << endl;
		tab[sz++] = elt;
		sem_post(&semaphore_empty);
		sem_post(&mutex);
	}
};

}
