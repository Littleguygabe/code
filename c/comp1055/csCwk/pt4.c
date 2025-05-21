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

#define PORT 1818

#define BUFFER_SIZE 512

void ServerConnection(int sd);
void ReadLineFromNetwork(int sd, char *buf, int size);

void getQuote(const char *filename, char *qotd, int quoteNum) {
    FILE *file;
    int i;

    file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "File not found: %s\n", filename);
        exit(2);
    }


    memset(qotd, 0, BUFFER_SIZE);

    for (i=0;i<quoteNum;i++){
        memset(qotd, 0, BUFFER_SIZE);       
        if (fgets(qotd, BUFFER_SIZE, file) == NULL) {
            fprintf(stderr, "Failed to read from file: %s\n", filename);
            fclose(file);
            exit(3);

        }

    }

    memset(qotd, 0, BUFFER_SIZE);
    
    if (fgets(qotd, BUFFER_SIZE, file) == NULL) {
        fprintf(stderr, "Failed to read from file: %s\n", filename);
        fclose(file);
        exit(3);

    }


    fclose(file);

    // Append '\r\n' if space allows
    size_t len = strlen(qotd);
    if (len + 2 <= BUFFER_SIZE) {
        qotd[len] = '\r';
        qotd[len + 1] = '\n';
        qotd[len + 2] = '\0';
    } else {
        fprintf(stderr, "Buffer not large enough to modify string\n");
        exit(1);
    }
}


int main(int argc, const char * argv[]){

    int serverSocket, connectionSocket;
    struct sockaddr_in server;
    struct sockaddr_in client;
    unsigned int alen;
    char qotd[BUFFER_SIZE];
    char recvBuf[BUFFER_SIZE];
    char * errorMsg = "ERROR\r\n\0";
    char * closeMsg = "BYE\r\n\0";

    FILE * file;

    int i;

    int anotherChoice = 1;
    int isError = 0;
    int bytesReceived;

    /*error checking for the file*/

    if (argc!=2){
        fprintf(stderr,"Incorrect number of arguments\n");
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
    while(1){
        i = 0;
        alen = sizeof(client);
        connectionSocket = accept(serverSocket,(struct sockaddr *)&client,&alen);
        anotherChoice = 1;

        /*the accept connection just waits forever until a connection is made
            then once connected it returns a new socket descriptor for the connection
            
            the new socket descriptor is what is held in the connection socket variable*/

        /*use this socket to communicate*/

       while (anotherChoice) {

            if (!isError) {
                getQuote(argv[1], qotd, i);
                i++;
                send(connectionSocket, qotd, strlen(qotd), 0);
            }
            isError = 0;

            int bytesReceived = recv(connectionSocket, recvBuf, BUFFER_SIZE - 1, 0);
            if (bytesReceived > 0) {
                recvBuf[bytesReceived] = '\0';
                recvBuf[strcspn(recvBuf, "\r\n")] = '\0';

                if (strcmp(recvBuf, "ANOTHER") == 0) {
                    continue;
                } else if (strcmp(recvBuf, "CLOSE") == 0) {
                    anotherChoice = 0;
                } else {
                    send(connectionSocket, errorMsg, strlen(errorMsg), 0);
                    isError = 1;
                }
            } else {
                anotherChoice = 0;
            }

            memset(recvBuf, 0, BUFFER_SIZE);
        }

        send(connectionSocket,closeMsg,strlen(closeMsg),0);
        close(connectionSocket);
 
    }

    return 0;
}