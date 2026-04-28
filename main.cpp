#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cassert>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/event.h>
#include <sys/time.h>

int open_clientfd(char *hostname, char *port)
{
    int clientfd = 0;
    struct addrinfo hints, *listp, *p;
    
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV;
    hints.ai_flags |= AI_ADDRCONFIG;
    
    if(getaddrinfo(hostname, port, &hints, &listp) != 0)
    {
        // log
        return -1;
    }
    for(p = listp; p; p = p -> ai_next)
    {
        if((clientfd = socket(p -> ai_family, p -> ai_socktype, p -> ai_protocol)) < 0)
            continue;
        
        if(connect(clientfd, p -> ai_addr, p -> ai_addrlen) != -1)
            break;
        close(clientfd);
    }
    
    freeaddrinfo(listp);
    if(!p)
        return -1;
    else
        return clientfd;
}

int open_listenfd(char *port)
{
    struct addrinfo hints, *listp, *p;
    int listenfd = -1, optval = 1;
    
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
    hints.ai_flags |= AI_NUMERICSERV;
    if(getaddrinfo(NULL, port, &hints, &listp) != 0)
    {
        // log
        return -1;
    }
    
    for(p = listp; p; p = p -> ai_next)
    {
        if((listenfd = socket(p -> ai_family, p -> ai_socktype, p -> ai_protocol)) < 0)
            continue;
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));
        
        if(bind(listenfd, p -> ai_addr, p -> ai_addrlen) == 0)
            break;
        close(listenfd);
    }
    
    freeaddrinfo(listp);
    if(!p)
        return -1;
    else
        return listenfd;
}

int main(int argc, char *argv[])
{
    if(argc <= 1)
    {
        printf("Usage: <file_name> <port>");
        return 1;
    }
    
    
}


