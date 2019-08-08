/*

	CLIENT SIDE
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

char *get_ip_address(){
    FILE *f;
    int ip_char_size = 16;      //maximum number of IP numbers and dots
    char *res = (char *)calloc(ip_char_size, sizeof(char));

    system("hostname -I > ip.txt");

    f = fopen("ip.txt", "r");

    if(f == NULL){
        printf("Unable to curl ifconfig.me\n");
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


int get_message(char buff[], int buff_size){
	int i = 0;

	while(i < buff_size - 1){
		buff[i++] = getchar();
	}

	buff[i] = '\0';

	return i;
}

void print_message(char buff[], int size){
    int i;
	for(i = 0; i < size; i++)
		putchar(buff[i]);
	putchar('\n');
}

int main(){
	int clientSocket, portNum, nBytes;
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	
	/*Create UDP socket*/
	clientSocket = socket(PF_INET, SOCK_DGRAM, 0);
	
	/*Configure settings in address struct*/
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(1234);

	// set up the ip address	
	serverAddr.sin_addr.s_addr = inet_addr(get_ip_address());

	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
	
	/*Initialize size variable to be used later on*/
	addr_size = sizeof serverAddr;
	
	int buff_size = 1024;
	char buff[buff_size];	
	
	printf("Starting communication...\n");
	while(1){ 
		fgets(buff, buff_size, stdin);
	
		nBytes = strlen(buff) + 1; 

		printf("===========\n");
	  
	  /*Send message to server*/
		sendto(clientSocket,buff,nBytes,0,(struct sockaddr *)&serverAddr,addr_size);
	
	  /*Receive message from server*/
		nBytes = recvfrom(clientSocket,buff, buff_size, 0, NULL, NULL);
	
		print_message(buff, nBytes);	  	
	}
	
	return 0;
}
