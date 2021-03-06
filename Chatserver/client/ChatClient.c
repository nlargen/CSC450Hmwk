#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    uint16_t port = 3000;
    int error;
    struct sockaddr_in* server = malloc(sizeof(struct sockaddr_in));
    server->sin_family = AF_INET;
    server->sin_addr.s_addr = INADDR_ANY;
    server->sin_port = htons( 8888 );
    //memset(server->sin_zero, '\0', sizeof server->sin_zero);
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    error = connect(sockfd, (struct sockaddr *)server, sizeof(struct sockaddr));
    if(error < 0)
    {
        puts("Problem with connecting...\n");
    }
    else
    {
        puts("We are Connected");
        //Receive a reply from the server
        
        char* server_reply = malloc(2000 * sizeof(char));
       
            error = recv(sockfd, server_reply,  (sizeof(server_reply)), 0);
            if(error < 0)
            {
                puts("recv failed");
                //break;
            }
            else
            {
                puts("Reply received\n");
                puts(server_reply);
                char* msg = "i hear you";
                send(sockfd , msg , strlen(msg) , 0);
               //break;
               
            }
        
        
    }
    free(server);
    return 0;
}