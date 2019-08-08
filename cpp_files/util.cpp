#include <string>

String get_ip(){
	FILE *f;
	string ip;
	
	system("curl -s ifconfig.me > ip.txt");
	
	f = fopen("ip.txt", "r");
	
	if(f == NULL){
	    printf("shiet\n");
	    return -1;
	}
	
	int i = 0;
	while(1){
	    if(fscanf(f, "%c", &res[i]) == 1)		// todo read input 
	        i++;
	    else{
	        res[i] = '\0';
	        break;
	    }
	}
	system("rm ip.txt");
	pclose(f);

}
