#include <cstddef>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
using namespace std;
int main(int argc, char* argv[]){
	if(argc < 3){
		return 1;
	}
	int tube[2];
	size_t i;
	for(i = 1; string(argv[i]) != "|"; i++){
		/*nop*/
	}
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
	return 0;
}