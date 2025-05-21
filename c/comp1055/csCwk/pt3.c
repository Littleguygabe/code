/*
 *  MultiQuoteClient
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

#define kMULTIQUOTEPORT 1818

int main(int argc, const char * argv[])
{

    if (argc!=3){
        fprintf(stderr,"incorrect number of arguments\n");
    }

    return 0;
}
