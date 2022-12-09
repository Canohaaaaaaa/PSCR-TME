#ifndef SRC_SERVERSOCKET_H_
#define SRC_SERVERSOCKET_H_

#include "Socket.h"

namespace pr {

class ServerSocket {
	int socketfd;

public :
	// Demarre l'ecoute sur le port donne
	ServerSocket(int port){
		int fd = socket(AF_INET, SOCK_STREAM, 0);
		struct sockaddr_in adr;
		adr.sin_family = AF_INET;
		adr.sin_port = htons(port);
		adr.sin_addr.s_addr = htonl(INADDR_ANY);
		if(bind(fd, (struct sockaddr *)& adr, sizeof(adr)) == -1){
			perror("bind");
		}
		listen(fd, 10);
		socketfd = fd;
	}

	int getFD() { return socketfd;}
	bool isOpen() const {return socketfd != -1;}

	Socket accept(){
		struct sockaddr_in exp;
		socklen_t sz = sizeof(exp);
		int fd = ::accept(socketfd, (struct sockaddr *)& exp, &sz);
		if(fd == -1){
			std::cout << "Echec" << std::endl;
			return Socket(fd);
		}
		std::cout << "Connexion recue de" << &exp << std::endl;
		return Socket(fd);
	}
	void close();
};

} // ns pr
#endif /* SRC_SERVERSOCKET_H_ */
