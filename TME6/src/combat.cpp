#include <cstddef>
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include "rsleep.h"
using namespace std;

int point_vie = 3;
char* nom = "Vador";

void degat(int sig){
	point_vie--;
	cout << nom << " a : " << point_vie << "PV" << endl;
	if(point_vie <= 0){
		cout << nom << " a perdu !" << endl;
		exit(1);
	}
}

void setup_handler(){
	struct sigaction handler_setup;
	handler_setup.sa_handler = degat;
	sigaction(SIGCHLD, &handler_setup, NULL);
}

void attaque(pid_t adversaire){
	setup_handler();
	cout << nom << " attaque !" <<  endl;
	int resultat = kill(adversaire, SIGCHLD);
	if(!(kill(adversaire, SIGCHLD) == -1)){
		randsleep();
	}
	else{
		cout << nom << " a gagné !" << endl;
		exit(0);
	}
}

void defense(){
	struct sigaction defense_ignore;
	defense_ignore.sa_handler =  SIG_IGN;
	sigaction(SIGCHLD, &defense_ignore, NULL);
	cout << nom << " bloque !" << endl;
	randsleep();
	defense_ignore.sa_handler =  degat;
	sigaction(SIGCHLD, &defense_ignore, NULL);
	cout << nom << " ne bloque plus." << endl;
}

void combat(pid_t adversaire){
	while(true){
		attaque(adversaire);
		defense();
	}
}

int main(void){
	pid_t pid_pere = getpid(); //Vador est le pere evidemment
	pid_t pid_fils = fork();
	setup_handler();

	if(pid_fils == -1){
		return 1;
	}
	else if(pid_fils){ //Vador
		cout << "Je suis " << nom << endl;
		cout << "Mon fils est " << pid_fils << endl;
		combat(pid_fils);
	} 
	else{ //Luke
		nom = "Luke";
		cout << "Je suis " << nom << endl;
		cout << "Mon pere est " << pid_pere << endl;
		combat(pid_pere);
	}
	return 0;
}