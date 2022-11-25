#include <cstddef>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
using namespace std;
int main(int argc, char* argv[]){
	if(argc < 3){
		perror("mauvais usage");
		return 1;
	}
	size_t i;
	//** Segmentation des commandes **//
	for(i = 1; string(argv[i]) != "|"; i++){
		/*nop*/
	}
	argv[i] = NULL;
	cout << "Commande 1 : " << endl;
	for(size_t j = 1; j < i; j++){
		cout << argv[j] << " ";
	}
	cout << endl;
	cout << "Commande 2 : " << endl;
	for(size_t k = i+1; k < argc; k++){
		cout << argv[k] << " ";
	}
	cout << endl;

	//** Pipe pere-fils **//
	int tube[2];
	pid_t pid_fils = fork();
	if (pid_fils == -1){
		return 1;
	}
	char** arg_commande;
	if(pipe(tube) == -1){
		perror("pipe");
		return 1;
	}
	if (pid_fils == 0) { //Fils
		arg_commande = &argv[i+1];
		//cout << arg_commande[0] << endl;
		dup2(tube[1],STDOUT_FILENO);
		close (tube[1]);
		close (tube[0]);
		if(execv(argv[i+1], &argv[i+1]) == -1){
			perror("execv");
			return 1;
		}
	}
	else { //Pere
		arg_commande = &argv[2];
		//cout << arg_commande[0] << endl;
		dup2(tube[0],STDIN_FILENO);
		close (tube[0]);
		close (tube[1]);
		if (execv(argv[1], &argv[1]) == -1) {
			perror ("execv");
			return 1;
		}
	}
	return 0;
}