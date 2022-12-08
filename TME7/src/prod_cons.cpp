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

int main () {
	int desc = shm_open("/stack_segment", O_RDWR | O_CREAT, 0600);
	if(desc == -1){
		perror("segment");
		return 1;
	} 
	Stack<char> * s = new Stack<char>();
	if(ftruncate(desc, sizeof(s)) == -1) {
		perror("ftruncate");
		exit(1);
	}
	int N = 2;
	int M = 3;
	pid_t pid_fils;
	for(int i = 0; i < N; i++){
		pid_fils = fork();
		if(pid_fils == 0){
			cout << "X" << endl;
			producteur(s);
			return 0;
		}
	}
	for(int i = 0; i < M; i++){
		pid_fils = fork();
		if(pid_fils == 0){
			consomateur(s);
			return 0;
		}
	}

	wait(0);
	wait(0);

	delete s;
	return 0;
}

