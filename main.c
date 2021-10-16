#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "lib/message.h"

int main(int argc, char *argv[])
{
	int socket_desc, client_sock, c, read_size = 0;
	struct sockaddr_in server, client;
	char client_message[2000];

	// Create socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");

	// Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8080);

	// Bind
	if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		// print the error message
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");

	// Listen
	listen(socket_desc, 3);

	// Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);

	for (;;)
	{
		// accept connection from an incoming client
		client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c);
		if (client_sock < 0)
		{
			perror("accept failed");
			return 1;
		}
		printf("Connection accepted with client socket: %d\n", client_sock);

		// Receive a message from client
		for (;;)
		{
			read_size = recv(client_sock, client_message, 2000, 0);
			printf("Client sent size of: %d\n", read_size);

			if (read_size > 0)
			{
				// Send the message back to client
				puts(client_message);
				write(client_sock, getmessage(), strlen(getmessage()));
			}

			if (read_size == -1)
			{
				perror("recv failed");
				shutdown(client_sock, 0);
				break;
			}
		}
	}

	close(socket_desc);

	return 0;
}