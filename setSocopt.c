#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
        int soc_desc, new_soc, c;
        struct sockaddr_in server, client;

        char *message;
        int optval;
        socklen_t optlen = sizeof(optval);

        //Create socket
        soc_desc = socket(AF_INET,SOCK_STREAM,0);
        if(soc_desc == -1)
        {
                printf("Could not create socket");
        }

        //Check the status for the keepalive option
        if(getsockopt(soc_desc,SOL_SOCKET,SO_KEEPALIVE,&optval,&optlen)<0)
        {
                perror("getsockopt()");
                close(soc_desc);
                exit(EXIT_FAILURE);
        }

        printf("SO_KEEPALIVE is %s\n",(optval ?"ON":"OFF"));

        //Set the option active

        optval=1;
        optlen=sizeof(optval);
        if(setsockopt(soc_desc,SOL_SOCKET,SO_KEEPALIVE,&optval,optlen)<0)
        {
                perror("setsockopt()");
                close(soc_desc);
                exit(EXIT_FAILURE);
        }

        printf("SO_KEEPALIVE set on socket\n");

        //Check the status again
        if(getsockopt(soc_desc,SOL_SOCKET,SO_KEEPALIVE,&optval,&optlen)<0)
        {
                perror("getsockopt()");
                close(soc_desc);
                exit(EXIT_FAILURE);
        }

        printf("SO_KEEPALIVE is %s\n",(optval ?"ON":"OFF"));

        //Prepare the sockaddr in structure
        server.sin_family=AF_INET;
        server.sin_addr.s_addr=INADDR_ANY;
        server.sin_port=htons(8888);

        //Bind
        if(bind(soc_desc,(struct sockaddr*)&server,sizeof(server))<0)
        {
                puts("Bind Failed");
                return 1;
        }
        puts("Bind Done");

        //Listen
        listen(soc_desc,3);
        //accept connectiong
        puts("Waiting for incoming connections. . .");
        c=sizeof(struct sockaddr_in);
        while(new_soc=accept(soc_desc,(struct sockaddr*)&client,(socklen_t*)&c))
        {
                puts("Connection accepted");

                //reply to the client
                message = "Hello Client, i have received your connection, but i have to go now, bye\n";
                write(new_soc,message,strlen(message));

        }
        if(new_soc<0)
        {
                perror("Accept Failed");
                return 1;
        }
        return 0;

}
