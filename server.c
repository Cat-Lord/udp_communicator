/*
	Simple client-server_addr application on UDP socket communication and basic (common) usage
	of given functions.

	SERVER side

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

char *get_ip_address(){
	FILE *f;
	int ip_char_size = 16;		//maximum number of IP numbers and dots
	char *res = (char *)calloc(ip_char_size, sizeof(char));
	
	system("hostname -I > ip.txt");
	
	f = fopen("ip.txt", "r");
	
	if(f == NULL){
	    printf("shiet\n");
	    return NULL;
	}
	
	int i = 0;
	while(i < ip_char_size - 1){
	    if(fscanf(f, "%c", &res[i]) == 1)
	        i++;
	    else
	        break;
	}
	system("rm ip.txt");
	pclose(f);	

	printf("Setting up ip address: %s\n", res);
	
	return res;
}

void print_message(char buff[], int size){
	int i;
	for(i = 0; i < size; i++)
		putchar(buff[i]);	
	putchar('\n');
}

void get_message(char buff[], int buff_size){
	int i = 0;
	while(i < buff_size-1){
		buff[i++] = getchar();
	}

	buff[i] = '\0';

	putchar('\n');
}

int main(){

	// create UDP socket
	int sock = socket(AF_INET, SOCK_DGRAM, 0);

	// server_addr socket address setup
	struct sockaddr_in server_addr;	
	server_addr.sin_family = AF_INET;		// ipv4
	server_addr.sin_port   = htons(1234);

	server_addr.sin_addr.s_addr = inet_addr(get_ip_address()); 

	// memset(server_addr.sin_zero, '\0', sizeof(server.sin_zero));

	bind(sock, (struct sockaddr *) &server_addr, sizeof(server_addr));

	struct sockaddr_storage server_addr_storage;
	socklen_t addr_size = sizeof(server_addr_storage);

	int n_bytes, 
		buff_size = 1024;
	char buff[buff_size];
	while(1){
		n_bytes = recvfrom(sock, buff, buff_size, 0, (struct sockaddr *) &server_addr_storage, &addr_size);

		print_message(buff, n_bytes);

		printf("---------\n");
	
		fgets(buff, buff_size, stdin);
		n_bytes = strlen(buff) + 1;

		sendto(sock, buff, n_bytes, 0, (struct sockaddr *) &server_addr_storage, addr_size);
	}

	return 0;
}
