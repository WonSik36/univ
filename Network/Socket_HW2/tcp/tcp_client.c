#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char* argv[]){
    int sd;
    FILE* fp;
	char buf[BUF_SIZE];
	int read_cnt;

    struct sockaddr_in serv_adr;
    if(argc != 4){
        printf("Usage: %s <IP> <port> <file_name>\n", argv[0]);
        exit(1);
    }

    // make file pointer
    fp = fopen(argv[3],"rb");
    if(fp == NULL)
        error_handling("fopen() error");

    // make socket
    sd = socket(PF_INET, SOCK_STREAM, 0);
    if(sd == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    if(connect(sd, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("connect() error");

    // send file name
    strcpy(buf,argv[3]);
    buf[strlen(buf)] = 0;
    send(sd,buf,strlen(buf)+1,0);
    // send file info
    while(1){
        read_cnt = fread((void*)buf,1,BUF_SIZE,fp);
        if(read_cnt<BUF_SIZE){
            send(sd,buf,read_cnt,0);
            break;
        }
        send(sd,buf,BUF_SIZE,0);
    }

    printf("file send complete\n");

    fclose(fp);
    close(sd);
    return 0;
}

void error_handling(char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
