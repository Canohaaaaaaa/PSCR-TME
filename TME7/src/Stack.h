#pragma once

#include <cstring> // size_t,memset
#include <semaphore.h>
#include <fcntl.h>
namespace pr {

#define STACKSIZE 100

template<typename T>
class Stack {
	T tab [STACKSIZE];
	size_t sz;
	sem_t* semaphore_conso;
	sem_t* semaphore_prod;
public :
	Stack () : sz(0) { 
		memset(tab,0,sizeof tab);
		semaphore_conso = sem_open("/stacksemconso", O_CREAT | O_RDWR, 0600, 1);
		semaphore_prod = sem_open("/stacksemprod", O_CREAT | O_RDWR, 0600, 1);
	}

	T pop () {
		if(!sz){
			sem_wait(semaphore_conso);
			T toret = tab[--sz];
			sem_post(semaphore_prod);
			return toret;
		}
		else{
			T toret = tab[--sz];
			return toret;
		}
	}

	void push(T elt) {
		if(sz == STACKSIZE){
			sem_wait(semaphore_prod);
			tab[sz++] = elt;
			sem_post(semaphore_conso);
		}
		else{
			tab[sz++] = elt;
		}
	}
};

}
