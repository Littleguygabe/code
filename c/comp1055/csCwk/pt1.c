/*
 *  QuoteClient
 *
 *  Created by Gabriel Bridger 
 *  Username: psygb6
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/socket.h>

#define kQUOTEPORT "1717"


void error_exit(const char *msg){
    fprintf(stderr,"error: %s\n",msg);
    exit(1);
}

int main(int argc, char * argv[]){
    const char* hostname;
    struct addrinfo hints, *res, *p;
    int sockfd;
    char buffer[512];
    ssize_t bytes_received;

    if (argc!=2){
        error_exit("Incorrect Number of Arguments");
    }

    hostname = argv[1];

    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_UNSPEC; /*stands for unspecified as havent specified what type of ip connecting to*/
    hints.ai_socktype = SOCK_STREAM;

    
    if (getaddrinfo(hostname,kQUOTEPORT,&hints,&res)!=0){
        error_exit("failed to get addr info");     
    }

    for (p=res;p!=NULL;p=p->ai_next){ /*res is a linked list of IPs that match the hints, so assign p to a node in the linked list then
    run through each node -p- until a successful match is found for the network connection, then once a connection is found the loop breaks
    */
        sockfd = socket(p->ai_family,p->ai_socktype,p->ai_protocol);
        if (sockfd==-1){
            continue;
        }
        if (connect(sockfd,p->ai_addr,p->ai_addrlen)==0){
            break;
        }

        close(sockfd); /*close connection and cycle to the next possible address
        like dynamic memory allocation, how have to close once opened otherwise can have unintended behaivours
        
        only called if the connection is unseccesful - if succesful then the loop breaks before the connection is closed so the open
        succesful connection is maintained*/
    }

    if (p==NULL){
        freeaddrinfo(res);
        error_exit("couldn't find a successful connection");
    }

    freeaddrinfo(res);

    bytes_received = recv(sockfd,buffer,sizeof(buffer)-1,0);
    if (bytes_received<0){
        error_exit("issue in receiving bytes from server");
    }

    buffer[bytes_received] = '\0';
    printf("QotD: %s",buffer);
    close(sockfd);

    return 0;
}