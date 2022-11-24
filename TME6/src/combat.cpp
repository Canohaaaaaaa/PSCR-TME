#include <cstddef>
#include <signal.h>
#include <iostream>
using namespace std;

int point_vie = 3;
void setup(int sig){
    point_vie--;
    cout << "Il me reste : " << point_vie << "PV" << endl;
    if(point_vie <= 0){
        //cout << "J'ai perdu !" << endl;
        exit(1);
    }
}
void attaque (pid_t adversaire){
    struct sigaction handler_setup;
    handler_setup.sa_handler = setup;
    sigaction(SIGCHLD, &handler_setup, NULL);
    if(!kill(adversaire, SIGCHLD) == -1){
        //TODO randsleep
    }
    else{
		exit(0);
	}
}

void defense(){
	sigset_t masque;
	sigemptyset(&masque);
	sigaddset (&masque, SIGCHLD);
	sigprocmask(SIG_SETMASK, &masque, NULL);
	//TODO randsleep
	sigprocmask(SIG_UNBLOCK, &masque, &masque);
}

int main(void){
    return 0;
}