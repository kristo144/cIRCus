#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void) {
	printf("Hello world!\n");
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr = {
		.sin_family = AF_INET,
		.sin_port = htons(6667),
		.sin_addr.s_addr = inet_addr("127.0.0.1"),
	};

	connect(sock, (struct sockaddr*) &addr, sizeof(addr));
	return 0;
}
