/*
    tcp protocol feature
    1. data is reliable
    2. data transport in order
    3. data boundary is not exist because tcp is connection oriented protocol
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void error_handling(char *message);

int main(int argc, char* argv[]){
    int sock;
    struct sockaddr_in serv_addr;
    char message[101];
	int buf_size = 101;

    if(argc != 3){
        printf("Usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    // 1.create socket
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    // 2.connection request to server
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error");

    // 3.send data to server
    // read() return length of byte which is read
	send(sock,"0123456789",10,0);
	send(sock,"ABCDEFGHIJ",10,0);
	send(sock,"abcdefghij",10,0);

	while(1){
		fputs("Input message(Q to quit): ",stdout);
		fgets(message, buf_size, stdin);
		if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
			break;

		send(sock, message, strlen(message),0);
    }	

    close(sock);
    return 0;
}

void error_handling(char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
