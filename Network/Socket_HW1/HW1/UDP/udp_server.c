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
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t adr_sz;
    int buf_size;
	int str_len, pid;

    if(argc != 3){
        printf("Usage: %s <port> <buf_size>\n", argv[0]);
        exit(1);
    }
    buf_size = atoi(argv[2]);

    // 1.create socket
    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    // 2.allocate IP address and Port#
    if(bind(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
        error_handling("bind() error");

    while(1){
        sleep(5);
        adr_sz = sizeof(clnt_addr);
        str_len = recvfrom(sock,message,buf_size,0,(struct sockaddr*)&clnt_addr,&adr_sz);
		message[str_len] = 0;
        if(strcmp(message, "q")==0)
            break;
        printf("Message from client: %s\n", message);
    }

    // 3-way handshake close
    pid = fork();
    if(pid == 0){
        while(1){
            sendto(sock,"ack",3,0,(struct sockaddr*)&clnt_addr, sizeof(clnt_addr));
            sleep(3);
        }
    }else{
        while(1){
            adr_sz = sizeof(clnt_addr);
            str_len = recvfrom(sock,message,buf_size,0,(struct sockaddr*)&clnt_addr,&adr_sz);
		    message[str_len] = 0;
            if(strcmp(message,"ack")==0)
                break;
        }
        kill(pid, SIGKILL);
    }

    close(sock);
    return 0;
}

void error_handling(char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
