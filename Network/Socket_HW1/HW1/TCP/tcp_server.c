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
    int serv_sock;
    int clnt_sock;
	int buf_size;
	int str_len;
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char message[101];

    if(argc != 3){
        printf("Usage: %s <port> <buf_size>\n", argv[0]);
        exit(1);
    }
	buf_size = atoi(argv[2]);

    // 1.create socket
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    // 2.allocate IP address and Port# by calling bind function
    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
        error_handling("bind() error");

    // 3.listen request
    if(listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    // 4.if connected with client, than return client socket
    clnt_addr_size = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if(clnt_sock == -1)
        error_handling("accept() error");

	// 5.get message and print it
	// if meet EOF than break
	while(1){
	    sleep(5);
		if((str_len = recv(clnt_sock,message,buf_size,0)) == 0)
			break;
		message[str_len] = 0;
		printf("message from client: %s\n",message);
	}

    close(clnt_sock);
    close(serv_sock);
    return 0;
}

void error_handling(char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
