#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include<sys/mman.h>
#include<sys/types.h>
#include <sys/stat.h>
#include <vector>
#include <fcntl.h>
using namespace std;
using namespace pr;
#define N 101
#define M 2
pid_t conso[M];

void producteur (Stack<char> * stack) {
	char c ;
	while (cin.get(c)) {
		stack->push(c);
	}
}

void consomateur (Stack<char> * stack) {
	while (true) {
		char c = stack->pop();
		cout << c << flush ;
	}
}

void destruction_conso(int signum){
	for(int i = 0; i < M; i++){
		kill(conso[i], SIGKILL);
	}
}

int main () {
	int desc = shm_open("/stack_segment", O_CREAT|O_RDWR|O_EXCL, 0600);
	struct sigaction handler_setup;
	handler_setup.sa_handler = destruction_conso;
	sigaction(SIGINT, &handler_setup, NULL);
	if(ftruncate(desc, sizeof(Stack<char>))){
		perror("ftruncate");
		exit(1);	
	}
	Stack<char> * stack;
	void *map = mmap(0, sizeof(Stack<char>), PROT_READ|PROT_WRITE, MAP_SHARED, desc, 0);
	if(desc == -1){
		perror("segment");
		return 1;
	} 
	stack = new (map)Stack<char>();
	pid_t pid_fils;
	for(int i = 0; i < N; i++){
		pid_fils = fork();
		if(pid_fils == 0){
			cout << "Nouveau prod" << endl;
			producteur(stack);
			return 0;
		}
	}

	for(int i = 0; i < M; i++){
		pid_fils = fork();
		conso[pid_fils] = pid_fils;
		if(pid_fils == 0){
			cout << "Nouveau conso" << endl;
			consomateur(stack);
			return 0;
		}
	}

	for(int i = 0; i < (N + M); i++){
		wait(0);
	}
	stack->~Stack();
	close(desc);
	shm_unlink("/stack_segment");
	munmap(map, sizeof(Stack<char>));
	return 0;
}

