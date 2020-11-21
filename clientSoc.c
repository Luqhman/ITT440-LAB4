#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int socket_desc;
	struct sockaddr_in server;
	char *message;
	char server_reply[2000];

	//Create Socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}

	server.sin_addr.s_addr = inet_addr("192.168.43.100");
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);

	//Connect to remote server
	if(connect(socket_desc,(struct sockaddr*)&server, sizeof(server))<0)
	{
		puts("connect error");
		return 1;
	}
	puts("Connected");

	//Send some data
	message = "connect";
	if (send (socket_desc, message, strlen(message), 0 ) < 0)
	{
		puts("Send data failed");
		return 1;
	}
	puts ("Data send\n");

	//Receive a reply from the server
	if( recv(socket_desc, server_reply, 2000, 0)<0)
	{
		puts("Receiving data failed");
		return 1;
	}
	puts ("This is server reply: \n");
	puts (server_reply);

	close(socket_desc);
	return 0;

}
