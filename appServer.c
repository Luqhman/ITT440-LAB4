#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    	int sock_desc, new_sock, c;
    	struct sockaddr_in server, client;
    	char server_mes[2000],client_mes[2000];

    	// Create socket
    	sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    	if(sock_desc == -1)
        	printf("Could not create socket.");

    	// Prepare the sockaddr_in structure
    	server.sin_family = AF_INET;
    	server.sin_addr.s_addr = INADDR_ANY;
    	server.sin_port = htons(8888);

    	// Bind the socket
    	if(bind(sock_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
        	puts("Bind failed.");

    	puts("Binding completed.\n");

	// Listen for connection
	listen(sock_desc, 3);

	//accept incoming connection
	puts("waiting for incoming connections . . .\n");
	c = sizeof(struct sockaddr_in);
	while(new_sock = accept(sock_desc,(struct sockaddr*)&client,(socklen_t*)&c))
	{
		puts("Connection established\n");
		//send data to client
		printf("Type anything: \n");
		scanf("%s",server_mes);
		send(new_sock,server_mes,2000,0);

		//receive data from client
		recv(new_sock,client_mes,2000,0);
		printf("Message from client: %s\n",client_mes);
	}
	if(new_sock < 0)
		perror("Connection Failed");

	return 0;

}
