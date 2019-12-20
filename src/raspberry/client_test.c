
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>


#define SERVER_IP   "192.168.1.169"
#define SERVER_PORT 1234
#define MAX_MSG_LEN 1024


int main(int argc, char const *argv[])
{
    int sockfd;
    struct sockaddr_in addr;
    int ret = 0;
    char *buf = "hello-server!";
    int bytes=0;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        fprintf(stderr, "Socket error: %s\n", strerror(errno));
        exit(1);
    }

    bzero(&addr, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    ret = inet_aton(SERVER_IP, &addr.sin_addr);
    if (ret < 0) {
        fprintf(stderr, "IP error: %s", strerror(errno));
        exit(1);
    }

    while (1)
    {
        bytes = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));
        if (bytes >= 0)
            fprintf(stdout, "Send %d byte data\n", bytes);
        else 
            fprintf(stderr, "Send error: %s\n", strerror(errno));

        sleep(1);
    }
    
    

    return 0;
}