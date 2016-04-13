#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>


int main(int argc, char** argv)
{
    uint16_t port = 3000; 
    struct sockaddr_in name; 
    name.sin_family = AF_INET; 
    name.sin_port = htons (port); 
    name.sin_addr.s_addr = hton1 (INADDR_ANY); 
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    int bindfd = bind (sockfd, (struct sockaddr *) &name, sizeof (name));
    int listenfd = listen(sockfd, 100); 
    printf("Listening \n"); 
    int clientfd = accept(sockfd, (struct sockaddr *) &name, sizeof (name));
    printf("client connected... \n"); 
    
}