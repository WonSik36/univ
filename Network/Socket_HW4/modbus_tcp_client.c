#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 100
#define PORT 502
#define UID 0x01

void readCoils(int sd);
void writeMultipleCoils(int sd);
void readHoldingRegisters(int sd);
void writeHoldingRegisters(int sd);
void addBit(char* input_bit, int idx);
void makeHeader(char* buf, short len);
void throwExceptionCode(char code);
void printOptions();
void error_handling(char *message);

int main(int argc, char* argv[]){
    int sd;
    struct sockaddr_in serv_adr;
    int opt;
    int flag = 1;

    if(argc != 2){
        printf("Usage: %s <IP>\n", argv[0]);
        exit(1);
    }

    // make socket
    sd = socket(PF_INET, SOCK_STREAM, 0);
    if(sd == -1)
        error_handling("socket() error");

    // set socket IP protocol, address and port
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons((int)502);

    // connect to server
    if(connect(sd, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("connect() error");

    // give seed to random function for tx id    
    srand(time(NULL));

    while(flag){
        // print functions
        printOptions();

        scanf("%d", &opt);

        switch(opt){
            case 1:
                readCoils(sd);
                break;
            case 2:
                writeMultipleCoils(sd);
                break;
            case 3:
                readHoldingRegisters(sd);
                break;
            case 4:
                writeHoldingRegisters(sd);
                break;
            case 100:
                flag = 0;
                break;
            default:
                printf("You enter wrong number\n\n");
                break;
        }
   
        printf("----------------------------------------\n\n");
    }

    close(sd);
    printf("bye~\n");
    return 0;
}

void readCoils(int sd){
    unsigned char buf[BUF_SIZE];
    int read_cnt;
    short start_adr, quantity;
    int i;

    printf("Enter the Start Address: ");
    scanf("%hd",&start_adr);
    printf("Enter number of coils to be read: ");
    scanf("%hd",&quantity);

    // header
    makeHeader(buf,6);

    // data
    buf[7] = 0x01; // Function Code
    buf[8] = (char)(start_adr/256); // starting address
    buf[9] = (char)(start_adr%256); // starting address
    buf[10] = (char)(quantity/256); // quantity of coils
    buf[11] = (char)(quantity%256); // quantity of coils

    // send data
    send(sd,buf,12,0);

    // recieve header, function code and number of coils
    recv(sd,buf,9,0);

    // error check
    if(buf[7] > 80){
        throwExceptionCode(buf[8]);
        return;
    }

    // check number of coil status
    read_cnt = recv(sd,buf,(int)buf[8],0);

    //print result
    printf("Data recieved in Hexadecimal\n");
    printf("----------------------------------------\n\n");
   
    printf("[First Address] [Last Address]: %04X %04X\n",start_adr,(start_adr+quantity-1));
    printf("[DATA]: ");
    for(i=0;i<read_cnt;i++){
        printf("%02X ",buf[i]);
    }
    printf("\n");

    return;
}

void writeMultipleCoils(int sd){
    unsigned char buf[BUF_SIZE];
    int read_cnt, input_cnt;
    short start_adr, quantity, max = 0;
    short * input;
    char * input_bit;
    char byte_cnt;
    int i;

    printf("Enter the Start Address: ");
    scanf("%hd",&start_adr);
    printf("Enter number of coils to be True(number of address you will type): ");
    scanf("%d",&input_cnt);
    input = (short*)malloc(input_cnt*sizeof(short));

    // check input is adequate
    if(input_cnt <= 0){
        printf("Wrong input\n");
        return;
    }

    // get input
    printf("Enter address of coils to be True(Not typed address will be false): ");

    for(i=0;i<input_cnt;i++){
        scanf("%hd", &input[i]);
        if(max<input[i]) max = input[i];
    }

    quantity = max - start_adr +1;
    byte_cnt = (char)ceil(quantity / 8.0f);
    input_bit = (char*)malloc(byte_cnt*sizeof(char));

     // initialize input bit
    for(i=0;i<byte_cnt;i++){
        input_bit[i] = 0;
    }

    // get input bit from input
    for(i=0;i<quantity;i++){
        addBit(input_bit, input[i]-start_adr);
    }

    // header
    makeHeader(buf,7+byte_cnt);

    // data
    buf[7] = 0x0F; // Function Code
    buf[8] = (char)(start_adr/256); // starting address
    buf[9] = (char)(start_adr%256); // starting address
    buf[10] = (char)(quantity/256); // quantity of coils
    buf[11] = (char)(quantity%256); // quantity of coils
    buf[12] = byte_cnt; // byte count


    for(i=0;i<byte_cnt;i++){
        buf[i+13] = input_bit[i];
    }

    // send data
    send(sd,buf,13+byte_cnt,0);

    // recieve header, function code and number of coils
    recv(sd,buf,9,0);

    // error check
    if(buf[7] > 80){
        throwExceptionCode(buf[8]);
        return;
    }

    // check number of coil status
    buf[0] = buf[8]; // starting address
    read_cnt = recv(sd,buf+1,3,0); // rest of starting adress and qunatity of output

    start_adr = 256*buf[0]+buf[1];
    quantity = 256*buf[2]+buf[3];

    //print result
    printf("Data recieved in Hexadecimal\n");
    printf("----------------------------------------\n\n");
   
    printf("[First Address] [Last Address]: %04X %04X\n",start_adr,start_adr+max);

    free(input);
    free(input_bit);
    return;
}

void readHoldingRegisters(int sd){
    unsigned char buf[BUF_SIZE];
    int read_cnt;
    short start_adr, quantity;
    int i;

    printf("Enter the Start Address: ");
    scanf("%hd",&start_adr);
    printf("Enter number of registers to be read: ");
    scanf("%hd",&quantity);

    // header
    makeHeader(buf,6);

    // data
    buf[7] = 0x03; // Function Code
    buf[8] = (char)(start_adr/256); // starting address
    buf[9] = (char)(start_adr%256); // starting address
    buf[10] = (char)(quantity/256); // quantity of registers
    buf[11] = (char)(quantity%256); // quantity of registers

    // send data
    send(sd,buf,12,0);

    // recieve header, function code and number of registers
    recv(sd,buf,9,0);

    // error check
    if(buf[7] > 80){
        throwExceptionCode(buf[8]);
        return;
    }

    // check number of register status
    read_cnt = recv(sd,buf,(int)buf[8],0);

    //print result
    printf("Data recieved in Hexadecimal\n");
    printf("----------------------------------------\n\n");
    
    printf("[First Address] [Last Address]: %04X %04X\n",start_adr,(start_adr+quantity-1));

    printf("[DATA]: ");
    for(i=0;i<read_cnt;i+=2){
        printf("%02X%02X ",buf[i],buf[i+1]);
    }
    printf("\n");

    return;
}

void writeHoldingRegisters(int sd){
    unsigned char buf[BUF_SIZE];
    int read_cnt, input_cnt;
    short start_adr, quantity, max = 0;
    short * input;
    int i;

    printf("Enter the Start Address: ");
    scanf("%hd",&start_adr);
    printf("Enter number of registers to be write(number of address you will type): ");
    scanf("%d",&input_cnt);
    input = (short*)malloc(input_cnt*sizeof(short));
    quantity = input_cnt*2;

    // check input is adequate
    if(input_cnt <= 0){
        printf("Wrong input\n");
        return;
    }

    // get input
    for(i=0;i<input_cnt;i++){
        printf("Enter value of registers[%04X]: ",start_adr+i);
        scanf("%hd", &input[i]);
        if(max<input[i]) max = input[i];
    }

    // header
    makeHeader(buf,7+quantity);

    // data
    buf[7] = 0x10; // Function Code
    buf[8] = (char)(start_adr/256); // starting address
    buf[9] = (char)(start_adr%256); // starting address
    buf[10] = (char)(quantity/256); // quantity of registers
    buf[11] = (char)(quantity%256); // quantity of registers
    buf[12] = quantity; // byte count

    for(i=0;i<quantity;i++){
        buf[2*i+13] = input[i]/256;
        buf[2*i+1+13] = input[i]%256;
    }

    // send data
    send(sd,buf,13+quantity,0);

    // recieve header, function code and number of registers
    recv(sd,buf,9,0);

    // error check
    if(buf[7] > 80){
        throwExceptionCode(buf[8]);
        return;
    }

    // check number of registers value
    buf[0] = buf[8]; // starting address
    read_cnt = recv(sd,buf+1,3,0); // rest of starting adress and qunatity of output

    start_adr = 256*buf[0]+buf[1];
    quantity = 256*buf[2]+buf[3];

    //print result
    printf("Data recieved in Hexadecimal\n");
    printf("----------------------------------------\n\n");
   
    printf("[First Address] [Last Address]: %04X %04X\n",start_adr,start_adr+max);

    free(input);
    return;
}

void addBit(char* input_bit, int idx){
    input_bit[idx/8] |= (1 << (idx%8));

}

void makeHeader(char* buf, short len){
    char r1,r2;

    // get random number
    r1 = (char)(rand()%256);
    r2 = (char)(rand()%256);

    // header(Big endian)
    buf[0] = r1; // Tx Id
    buf[1] = r2; // Tx Id
    buf[2] = 0x00; // Protocol Id
    buf[3] = 0x00; // Protocol Id
    buf[4] = (char)(len/256); // length
    buf[5] = (char)(len%256); // length
    buf[6] = UID; // Unit Identifier
}

void printOptions(){
    printf("Which function do you want?\n");
    printf("[1]: Read Coils\n");
    printf("[2]: Write multiple Coils\n");
    printf("[3]: Read Holding Registers\n");
    printf("[4]: Write multiple (Holding) Registers\n");
    printf("[100]: Quit\n");
    printf("Select a function [1,2,3,4,100]: ");
}

void throwExceptionCode(char code){
    printf("Error Occur with Exception Code: %d\n",code);
}

void error_handling(char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}