#include <ctime>
#include <cstdlib>
#include "rsleep.h"
#include <unistd.h>
void randsleep() {
  srand(getpid()); //Question 5, j'utilise le PID ici pour etre sur a 100% que la graine est differente
  int r = rand();
  double ratio = (double)r / (double) RAND_MAX;
  struct timespec tosleep;
  tosleep.tv_sec =0;
  // 300 millions de ns = 0.3 secondes
  tosleep.tv_nsec = 300000000 + ratio*700000000;
  struct timespec remain;
  /*
  La fonction nanosleep va nous reveiller lorsqu'on va recevoir le signal SIGINT et mettre le temps restant dans remain (puis tosleep).
  Cela nous permet d'executer notre handler puis de directement nous rendormir pour le temps qu'il nous reste lorsque par exemple on ce prend un coup.
  */
  while ( nanosleep(&tosleep, &remain) != 0) {
    tosleep = remain;
  }
}
