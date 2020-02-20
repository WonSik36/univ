/*
    upd protocol feature
    1. data is not reliable
    2. data transport out of order
    3. message oriented communication
    4. connectionless
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>

void error_handling(char *message);

int main(int argc, char* argv[]){
    int sock;
	char message[101];
    struct sockaddr_in serv_addr;
    socklen_t adr_sz;
    int pid,i;

    if(argc != 3){
        printf("Usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    // 1.create socket
    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    sendto(sock,"0123456789",10,0,(struct sockaddr*)&serv_addr, sizeof(serv_addr));
    sendto(sock,"ABCDEFGHIJ",10,0,(struct sockaddr*)&serv_addr, sizeof(serv_addr));
    sendto(sock,"abcdefghij",10,0,(struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
    while(1){
		fputs("Input message(Q to quit): ",stdout);
		fgets(message, 101, stdin);
		if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
			break;

		sendto(sock,message,strlen(message),0,(struct sockaddr*)&serv_addr, sizeof(serv_addr));
    }	
    
    // 3-way handshake close
    pid = fork();
    if(pid == 0){
        while(1){
            sleep(5);
            sendto(sock,"q",1,0,(struct sockaddr*)&serv_addr, sizeof(serv_addr));
        }
    }else{
        adr_sz = sizeof(serv_addr);
        recvfrom(sock,message,100,0,(struct sockaddr*)&serv_addr,&adr_sz);
        kill(pid, SIGKILL);
    }
    for(i=0;i<10;i++){
        sendto(sock,"ack",3,0,(struct sockaddr*)&serv_addr, sizeof(serv_addr));
    }
	
    close(sock);
    return 0;
}

void error_handling(char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
