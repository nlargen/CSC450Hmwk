#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void broadcast(char* msg, int* clients, int numClients);
void replied(int clientfd, int* clients, int numClients);
int main(int argc, char** argv)
{
    uint16_t port = 3000;
    struct sockaddr_in* server = malloc(sizeof(struct sockaddr_in));
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        puts("Bad Socket!!!!");
    }
    
    server->sin_family = AF_INET;
    server->sin_addr.s_addr = inet_addr("127.0.0.1");
    server->sin_port = htons( port );
    memset(server->sin_zero, '\0', sizeof server->sin_zero);

    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
		perror("setsockopt");
		exit(1);
	}
    socklen_t serverSize = sizeof(server);
    
    int bindfd = bind(sockfd, (struct sockaddr *)server, sizeof(struct sockaddr));
    if(bindfd < 0)
    {
        puts("Problem with binding...\n");
    }
    int listenfd;
    int clientfd;
    int error; 
    int MAX_CLIENTS = 5;
    int* clients = malloc(MAX_CLIENTS * sizeof(int));
    int numberOfConnectedClients = 0;
    while(1)
    {
        listenfd = listen(sockfd, 100);
    
        printf("Listening....\n");
        clientfd = accept(sockfd ,  (struct sockaddr *)server , &serverSize);
        printf("Client Connected.... %d\n", clientfd);
        //add this client to our array of clients
        clients[numberOfConnectedClients++] =  clientfd;
        char* message = "hello";
        broadcast(message, clients, numberOfConnectedClients);
       replied(clientfd, clients, numberOfConnectedClients);
       
    }
    
        
    
    //write(clientfd, buffer, sizeof(buffer));
}

void broadcast(char* msg, int* clients, int numClients)
{
    int i;
    for(i = 0; i < numClients; i++)
    {
       send(clients[i] , msg , (2 * (strlen(msg))) , 0);
        printf("Sending to client: %d\n", clients + (i * sizeof(int)));
        
    }
}
void replied(int clientfd, int* clients, int numClients)
{
    char* server_reply = malloc(2000 * sizeof(char));
       // int i; 
        //for(i = 0; i < numClients; i++)
        
        int errorc;
        errorc = recv(clientfd, server_reply, (4 * (sizeof(server_reply))), 0);
            if(errorc < 0)
            {
                puts("recv failed");
                puts(server_reply);
            }
            else
            {
                puts("Reply received\n");
                puts(server_reply);
               // broadcast(char* msg, )
               broadcast(server_reply, clients, numClients);
            }
        
}
