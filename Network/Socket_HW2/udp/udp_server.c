#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void error_handling(char *message);
int checkEOF(uint8_t buf[]);

int main(int argc, char* argv[]){
    int serv_sd;
    FILE* fp;
	char buf[BUF_SIZE];
	int read_cnt;

    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;


    if(argc != 2){
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    // make file socket
    serv_sd = socket(PF_INET, SOCK_DGRAM, 0);
    if(serv_sd == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    // 2.allocate IP address and Port# by calling bind function
    if(bind(serv_sd, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
        error_handling("bind() error");

    while(1){
        clnt_adr_sz = sizeof(clnt_adr);
        // receive file name
        recvfrom(serv_sd,buf,BUF_SIZE,0,(struct sockaddr*)&clnt_adr, &clnt_adr_sz);

        // make file pointer
        fp = fopen(buf,"wb");
        printf("file name is %s\n",buf);

        // receive file
        while((read_cnt=recvfrom(serv_sd,buf,BUF_SIZE,0,(struct sockaddr*)&clnt_adr, &clnt_adr_sz))!=0){

            if(checkEOF(buf))
                break;
            
            fwrite((void*)buf,1,read_cnt,fp);
        }

        printf("file transmission complete\n");
        fclose(fp);
    }

    close(serv_sd);
    return 0;
}

void error_handling(char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int checkEOF(uint8_t buf[]){
    if(buf[0] != 'E')
        return 0;
    if(buf[1] != 'O')
        return 0;
    if(buf[2] != 'F')
        return 0;
    
    return 1;
}