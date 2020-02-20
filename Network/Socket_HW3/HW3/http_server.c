#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define BUF_SIZE 1024
#define SMALL_BUF 100

void* request_handler(void* arg);
void route_handling(FILE* clnt_write, char* method, char* file_name, char* form_data);
void send_data_post(FILE* fp, char* form_data);
void send_data(FILE* fp, char* file_name);
void send_error(FILE* fp);
void error_handling(char* message);

int main(int argc, char *argv[]){
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	int clnt_adr_size;
	char buf[BUF_SIZE];
	pthread_t t_id;

	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	
    // make socket
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");

	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");

	while(1){
		clnt_adr_size = sizeof(clnt_adr);
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_size);
        printf("client socket : %d\n",clnt_sock);
		printf("Connection Request : %s:%d\n", inet_ntoa(clnt_adr.sin_addr), ntohs(clnt_adr.sin_port));
        pthread_create(&t_id, NULL, request_handler, &clnt_sock);
		pthread_detach(t_id);
	}

	close(serv_sock);
	return 0;
}

void* request_handler(void *arg){
    int clnt_sock=*((int*)arg);
	char req_line[SMALL_BUF];
	FILE* clnt_read;
	FILE* clnt_write;
	
	char method[10];
	char file_name[30];
    
	int buf_len = SMALL_BUF;
	int size;

	clnt_read = fdopen(clnt_sock, "r");
	clnt_write = fdopen(dup(clnt_sock), "w");
	fgets(req_line, SMALL_BUF, clnt_read);	
	
    if(strstr(req_line, "HTTP/")==NULL){
		send_error(clnt_write);
		fclose(clnt_read);
        printf("Connection Closed\n");
		return;
	}

	strcpy(method, strtok(req_line, " /"));
	strcpy(file_name, strtok(NULL, " /"));
    if(strcmp(method,"POST")==0){
        while(1){
			size = fgets(req_line, buf_len, clnt_read);
			
			// EOF
			if(size == 0)
				break;

			// get Form Data
            if(strstr(req_line, "name")!=NULL && strstr(req_line, "snumber")!=NULL)
                break;

			// content length
			if(strstr(req_line, "Content-Length: ")){
				buf_len = atoi(req_line+16)+1;  // strlen("Content-Length: ") = 16
				printf("Content-Length: %d\n",buf_len);
			}
            
        }
        // printf("request line: %s\n",req_line);
    }
    fclose(clnt_read);

    route_handling(clnt_write, method, file_name, req_line);
}


void route_handling(FILE* clnt_write, char* method, char* file_name, char* form_data){
    printf("%s %s\n",method, file_name);


    // GET method, /index.html
    if(strcmp(method, "GET")==0 && (strcmp(file_name, "HTTP")==0 || strcmp(file_name, "index.html")==0)){
        send_data(clnt_write, "index.html");
        return; 
    }

    // GET method, /query.html
    if(strcmp(method, "GET")==0 && strcmp(file_name, "query.html")==0){
        send_data(clnt_write, "query.html"); 
        return;
    }

    // POST method, /sample
    if(strcmp(method, "POST")==0 && strcmp(file_name, "sample")==0){
        send_data_post(clnt_write, form_data);
        return;
    }
    
    send_error(clnt_write);
    return;
}

void send_data_post(FILE* fp, char* form_data){
	char protocol[]="HTTP/1.0 200 OK\r\n";
	char server[]="Server:Linux Web Server \r\n";
	char cnt_len[SMALL_BUF];
	char cnt_type[] = "Content-type:text/html\r\n\r\n";
	char body[] = "<!DOCTYPE html><html><body><h2>%s</h2></body></html>";
    char buf[BUF_SIZE];
    int size;
	
    // make body
    sprintf(buf, body, form_data);

    // get size of total body
    size = strlen(buf);
    sprintf(cnt_len, "Content-length:%d\r\n", size);

	// send header
	fputs(protocol, fp);
	fputs(server, fp);
	fputs(cnt_len, fp);
	fputs(cnt_type, fp);

	// send body
	fputs(buf, fp);

	fflush(fp);
	fclose(fp);
    printf("Connection Closed\n");
}

void send_data(FILE* fp, char* file_name){
	char protocol[]="HTTP/1.0 200 OK\r\n";
	char server[]="Server:Linux Web Server \r\n";
	char cnt_len[SMALL_BUF];
	char cnt_type[] = "Content-type:text/html\r\n\r\n";
	char buf[BUF_SIZE];
	FILE* send_file;
    int size;
	
	send_file = fopen(file_name, "r");
	if(send_file==NULL){
		send_error(fp);
		return;
	}

    // get size of file
    fseek(send_file, 0, SEEK_END);
    size = ftell(fp);
    fseek(send_file, 0, SEEK_SET);
    sprintf(cnt_len, "Content-length:%d\r\n", size);

	// send header
	fputs(protocol, fp);
	fputs(server, fp);
	fputs(cnt_len, fp);
	fputs(cnt_type, fp);

	// send body
	while(fgets(buf, BUF_SIZE, send_file)!=NULL) {
		fputs(buf, fp);
		fflush(fp);
	}

	fflush(fp);
	fclose(fp);
    fclose(send_file);
    printf("Connection Closed\n");
}

void send_error(FILE* fp){	
	char protocol[]="HTTP/1.0 404 Not Found\r\n";
	char server[]="Server:Linux Web Server \r\n";
	char cnt_len[]="Content-length:154\r\n";
	char cnt_type[]="Content-type:text/html\r\n\r\n";
    char buf[BUF_SIZE];
    FILE* send_file = fopen("404_error.html", "r");

    // send header
	fputs(protocol, fp);
	fputs(server, fp);
	fputs(cnt_len, fp);
	fputs(cnt_type, fp);

    // send body
	while(fgets(buf, BUF_SIZE, send_file)!=NULL) {
		fputs(buf, fp);
		fflush(fp);
	}
    
	fflush(fp);
    fclose(fp);
    fclose(send_file);
    printf("Connection Closed\n");
}

void error_handling(char* message){
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}