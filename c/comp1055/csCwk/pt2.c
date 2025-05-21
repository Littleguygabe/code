#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>

#define kBufSize 12
#define WAITING 0
#define SENTKNOCKKNOCK 1
#define SENTCLUE 2
#define ANOTHER 3
#define BYE 4

#define kNUMCLUES 5

#define PORT 1717

#define BUFFER_SIZE 512

void ServerConnection(int sd);
void ReadLineFromNetwork(int sd, char *buf, int size);

int main(int argc, const char * argv[]){

    int serverSocket, connectionSocket;
    struct sockaddr_in server;
    struct sockaddr_in client;
    unsigned int alen;
    char qotd[BUFFER_SIZE];

    FILE * file;

    /*error checking for the file*/

    if (argc!=2){
        fprintf(stderr,"Incorrect number of arguments\n");
        return 1;
    }

    file = fopen(argv[1],"r");
    if (file==NULL){
        fprintf(stderr,"file directory not found\n");
    }

    fgets(qotd,sizeof(qotd),file);

    fclose(file);

    if (strlen(qotd)+2<=BUFFER_SIZE){
        qotd[strlen(qotd)] = '\r';
        qotd[strlen(qotd)+1] = '\n';
    }

    else{
        fprintf(stderr,"Buffer not large enough to correctly modify string\n");
        return 1;
    }

    serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    /*setup the socket port*/

    memset(&server,0,sizeof(struct sockaddr_in));
    server.sin_family = AF_INET; /*INET means ipv4*/
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    if(bind(serverSocket,(struct sockaddr *)&server,sizeof(struct sockaddr_in))<0){
        fprintf(stderr,"failed to bind()\n");
        exit(1);
    }

    /*listen for connections*/

    if(listen(serverSocket,15)<0){
        fprintf(stderr,"failed to listen()\n");
        exit(2);
    }

    /*accept the connection*/
    printf("waiting to accept connection\n");
    alen = sizeof(client);
    connectionSocket = accept(serverSocket,(struct sockaddr *)&client,&alen); 

    /*the accept connection just waits forever until a connection is made
        then once connected it returns a new socket descriptor for the connection
        
        the new socket descriptor is what is held in the connection socket variable*/

    /*use this socket to communicate*/

    printf("connection from %x on port %d\n",ntohl(client.sin_addr.s_addr),ntohs(client.sin_port));

    send(connectionSocket,qotd,strlen(qotd),0);
    close(connectionSocket);

    return 0;
}