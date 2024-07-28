#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <string.h>

char buffer[2048];

#define sendm(sockfd, msg) send((sockfd), (msg), strlen((msg)), 0)

int main(void) {
	printf("Hello world!\n");
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr = {
		.sin_family = AF_INET,
		.sin_port = htons(6667),
		.sin_addr.s_addr = inet_addr("127.0.0.1"),
	};

	connect(sock, (struct sockaddr*) &addr, sizeof(addr));
	sendm(sock, "NICK circus\r\n");
	sendm(sock, "USER circus localhost localhost :circus\r\n");

	struct pollfd fd = {
		.fd = sock,
		.events = POLLIN,
	};

	// Main loop
	for(;;) {
		int received = poll(&fd, 1, 100);
		if (received > 0) {
			ssize_t len = recv(sock, buffer, 2048, 0);
			if (!strncmp(buffer, "PING", 4)) {
				sendm(sock, "PONG :localhost.localdomain\r\n");
			}
			else {
				buffer[len] = '\0';
				printf("%s", buffer);
			}
		}
	}
	return 0;
}
