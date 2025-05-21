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
#include <pthread.h> /*needed to watch for multiple conns*/
#include <sys/socket.h>

#define kQUOTEPORT 1717

int main(int argc, const char * argv[])
{
    char buf[512];
    char line[512];
    int sd;
    char c;
    int n;
    int ret;
    struct addrinfo hints;
    struct sockaddr_in sa;
    struct addrinfo *ips;
    int quit=0;

    memset(&hints,o,sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if(!(ret = getaddrinfo("arrow.cs.nott.ac.uk","http",&hints,&ip))){
        struct addrinfo *p = ip;

        while(p){
            sd = socket(p->ai_family,p->ai_socktype,p->ai_protocol);

            if (sd!=-1){
                if (connect(sd,p->ai_addr,p->ai_addrlen)==0){
                    break;
                }
                else{
                    close(sd);
                    sd=-1;
                }
            }
            p=p->ai_next;
        }
    }
    else{
        printf("%d\n",ret);
        exit(1);
    }

 

    close(sd);
    return 0;
}