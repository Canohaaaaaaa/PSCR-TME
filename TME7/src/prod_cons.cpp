#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
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
	int desc;
	Stack<char> * s = new Stack<char>();
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

