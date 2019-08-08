/*
	Simple client-server_addr application on UDP socket communication and basic (common) usage
	of given functions.

	SERVER side

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>


int main(){

	// create UDP socket
	int sock = socket(AF_INET, SOCK_DGRAM, 0);

	// server_addr socket address setup
	struct sockaddr_in server_addr;	
	server_addr.sin_family = AF_INET;		// ipv4
	server_addr.sin_port   = htons(1234);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	// memset(server_addr.sin_zero, '\0', sizeof(server.sin_zero));


	bind(sock, (struct sockaddr *) &server_addr, sizeof(server_addr));

	struct sockaddr_storage server_addr_storage;
	socklen_t addr_size = sizeof(server_addr_storage);

	int n_bytes;
	char buff[1024];
	while(1){
		n_bytes = recvfrom(sock, buff, 1024, 0, (struct sockaddr *) &server_addr_storage, &addr_size);
		printf("Recieved\n");
		sendto(sock, buff, n_bytes, 0, (struct sockaddr *) &server_addr_storage, addr_size);
	}

	return 0;
}
