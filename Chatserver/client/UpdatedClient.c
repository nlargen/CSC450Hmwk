#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char** argv)
{
    uint16_t port = 4000;
    int error;
    struct sockaddr_in* server = malloc(sizeof(struct sockaddr_in));
    server->sin_addr.s_addr = inet_addr("127.0.0.1");
    server->sin_family = AF_INET;
    server->sin_port = htons( port );
    //memset(server->sin_zero, '\0', sizeof server->sin_zero);
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    error = connect(sockfd, (struct sockaddr *)server, sizeof(struct sockaddr));
    if(error < 0)
    {
        puts("Problem with connecting...\n");
    }
    else
    {
       int pid = fork();
       if(pid == 0)
       {
           childStuff(sockfd);
          
       }
       else 
       {
           parentStuff(sockfd);
       }
    }
    free(server);
    return 0;
}

void childStuff(int sockfd)
{
    int error;
    //Receive a reply from the server
    int MAX_SIZE = 2000 * sizeof(char);
    char* server_reply = malloc(MAX_SIZE);
    while(1)
    {
        puts("Waiting to recv");
        error = recv(sockfd, server_reply, MAX_SIZE, 0);
        if(error < 0)
        {
            puts("recv failed");
        }
        else
        {
            puts(server_reply);
            server_reply = malloc(MAX_SIZE);
            free(server_reply);
            //server_reply[0] = '\0';
        }
    }
}

void parentStuff(int sockfd)
{
    char* command;
    char* who;
    char* msg;
    while(1)
    {
        scanf("%ms", &command);
        if(strcmp("tell", command) == 0)
        {
            scanf("%ms %m[^\n]", &who, &msg);
            printf("Sending private message (%s) to: %s\n", msg, who);
        }
        else
        {
            scanf("%m[^\n]", &msg);
            char* destination = malloc(sizeof(command) + sizeof(msg));
            strcpy(destination, command);
            strcat(destination, msg);
            send(sockfd, destination , strlen(destination) , 0);
        } 
    }
}

