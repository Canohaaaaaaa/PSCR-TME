#ifndef SRC_SOCKET_H_
#define SRC_SOCKET_H_

#include <netinet/ip.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <iosfwd>
#include <iostream>
#include <unistd.h>

namespace pr {

class Socket {
	int fd;

public :
	Socket():fd(-1){}
	Socket(int fd):fd(fd){}

	// tente de se connecter à l'hôte fourni
	void connect(const std::string & host, int port){
		struct addrinfo * adr;
		getaddrinfo(host.c_str(), NULL, NULL, &adr);
		in_addr ipv4 = ((sockaddr_in *)adr->ai_addr)->sin_addr;
		freeaddrinfo(adr);
		connect(ipv4, port);
		return;
	}
	void connect(in_addr ipv4, int port){
		fd = socket(AF_INET, SOCK_STREAM, 0);
		struct sockaddr_in adr;
		adr.sin_family = AF_INET;
		adr.sin_port = htons(port);
		::connect(fd, (struct sockaddr *) &adr, sizeof(adr));
	}

	bool isOpen() const {return fd != -1;}
	int getFD() { return fd ;}

	void close(){
		if(isOpen()){
			shutdown(fd, SHUT_RDWR);
			::close(fd);
		}
	}
};
/*
std::ostream & operator<< (std::ostream & os, struct sockaddr_in * addr){
	char host[1024];
	
	getnameinfo((struct sockaddr *) addr, sizeof(struct sockaddr), host, 1024, NULL, 0, 0);
	os << "Machine" << host << std::endl;
	os << inet_ntoa(addr->sin_addr) << ":" << ntohs(addr->sin_port) << std::endl;

	return os;
}
*/

}

#endif /* SRC_SOCKET_H_ */
