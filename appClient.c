#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int sock_desc;
	struct sockaddr_in server;
	char client_mes[2000],server_mes[2000];

	//create socket
	sock_desc=socket(AF_INET,SOCK_STREAM,0);
	if(sock_desc == -1)
	{
		printf("Could not create socket\n");
	}

	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("192.168.43.100");
	server.sin_port=htons(8888);

	//connect to remote server
	if(connect(sock_desc,(struct sockaddr*)&server,sizeof(server))<0)
	{
		puts("Connection error");
		return 1;
	}

	puts("Connected");

	//send some data
	printf("Type something :");
	scanf("%s",client_mes);
	send(sock_desc,client_mes,2000,0);
	puts("Data sent");

	//Receive reply from server
	if(recv(sock_desc,server_mes,2000,0)<0)
	{
		puts("Failed to receive reply from server");
		return 1;
	}
	printf("Reply from server : %s\n",server_mes);
	close(sock_desc);

	return 0;
}
