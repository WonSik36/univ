#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "net.h"

#define BUF_SIZE 30
#define PROTO_UDP 17

#define PUBLIC_IP "203.252.106.83"
#define PRIVATE_IP "10.1.0.1"
#define IP PUBLIC_IP

void error_handling(char *message);
int checkEOF(uint8_t buf[]);
uint8_t* ntoarr(char* serv_addr, struct in_addr clnt_addr);

int main(int argc, char* argv[]){
    int serv_sd;
    FILE* fp;
	uint8_t buf[BUF_SIZE];
	uint16_t read_cnt;
    uint16_t cs;
    uint8_t* IpSum;
    int i;

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

    // 3.listen request of connection
	// 5 is wait queue

    while(1){
        clnt_adr_sz = sizeof(clnt_adr);
        // receive file name
        recvfrom(serv_sd,buf,BUF_SIZE,0,(struct sockaddr*)&clnt_adr, &clnt_adr_sz);

        IpSum = ntoarr(IP,clnt_adr.sin_addr);
        // for(i=0;i<4;i++){
        //     printf("%d ",cIp[i]);
        // }
        // printf("\n");

        // make file pointer
        fp = fopen(buf,"wb");
        printf("file name is %s\n",buf);

        // receive file
        while((read_cnt=recvfrom(serv_sd,buf,BUF_SIZE,0,(struct sockaddr*)&clnt_adr, &clnt_adr_sz))!=0){
            // uint16_t net_checksum_tcpudp(uint16_t length, uint16_t proto, uint8_t *addrs, uint8_t *buf);
            cs = net_checksum_tcpudp(read_cnt, PROTO_UDP,IpSum,buf);
            printf("%x\n",cs);


            if(checkEOF(buf))
                break;
            
            fwrite((void*)buf,1,read_cnt,fp);
        }

        printf("file transmission complete\n");
        fclose(fp);
        free(IpSum);
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

// addr: serv_adr.sin_addr
uint8_t* ntoarr(char* serv_addr, struct in_addr clnt_addr){
    uint8_t* res = (uint8_t*)malloc(sizeof(uint8_t)*4);
    uint8_t* str_ptr;
    uint8_t str_arr[20];
    uint8_t bf[5];
    int cnt = 0;
    int res_cnt = 0;
    int i;

    str_ptr = inet_ntoa(clnt_addr);
    strcpy(str_arr, str_ptr);
    printf("%s\n",str_arr);
    for(i=0;i<20&&str_arr[i]!=0;i++){
        if(str_arr[i] == '.'){
            bf[cnt] = 0;
            res[res_cnt++] = atoi(bf);
            cnt = 0;
            continue;
        }
        bf[cnt++] = str_arr[i];
    }
    bf[cnt] = 0;
    res[res_cnt++] = atoi(bf);

    return res;
}