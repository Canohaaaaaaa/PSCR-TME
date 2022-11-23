#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main () {
	const int N = 3;
	std::cout << "main pid=" << getpid() << std::endl;
	int nbFils = 0;
	int i;
	for (i=1, j=N; i<=N && j==N && fork()==0 ; i++ ) {
		nbFils = 0;
		std::cout << " i:j " << i << ":" << j << std::endl;
		for (int k=1; k<=i && j==N ; k++) {
			if ( fork() == 0) {
				nbFils = 0;
				j=0;
				std::cout << " k:j " << k << ":" << j << std::endl;
			}
			else{
				nbFils++;
			}
		}
	}
	if(!(i >= N)) //Le dernier fils ne fork pas a cause de la condition de fin
		nbFils++;
	std::cout << "nbFils : " << nbFils << std::endl;
	for(int i=0; i < nbFils; i++){
		wait(nullptr);
	}
	return 0;
}
