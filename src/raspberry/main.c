
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

#define SERVER_PORT 1234
#define MAX_MSG_LEN 1024


struct raw_data {
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    int16_t t;
}data;


int udp_recv(int sockfd)
{
    int addrlen;
    char msg[MAX_MSG_LEN];
    int bytes=0;
    struct sockaddr_in addr;

    fprintf(stdout, "Waiting client data...\n");
    while (1) {
        bzero(&data, sizeof(data));
        addrlen = sizeof(struct sockaddr); 
        // bytes = recvfrom(sockfd, msg, 128, 0, (struct sockaddr*)&addr, &addrlen);
        bytes = recvfrom(sockfd, &data, sizeof(data), 0, (struct sockaddr*)&addr, &addrlen);
        // msg[bytes] = 0;


        // fprintf(stdout, "from client [%s:%hu] say: \n%s\n\n", inet_ntoa(addr.sin_addr), \
        //     ntohs(addr.sin_port), msg);

        fprintf(stdout, "[%s:%hu]: Ax:%hd  Ay:%hd  Az:%hd  Gx:%hd  Gy:%hd  Gz:%hd  T:%hd\n", \
            inet_ntoa(addr.sin_addr), ntohs(addr.sin_port),
            data.ax, data.ay, data.az, data.gx, data.gy, data.gz, data.t);
    }
}


int main(int argc, char const *argv[])
{
    int sockfd;
    struct sockaddr_in addr;
    int ret=0;

    //udp, 数据包套接字
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        fprintf(stderr, "Socket error: %s\n", strerror(errno));
        exit(1);
    }

    bzero(&addr, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port=htons(SERVER_PORT);

    ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));
    if (ret < 0) {
        fprintf(stderr, "Socket error: %s\n", strerror(errno));
        close(sockfd);
        exit(1);
    }

    udp_recv(sockfd);
    

    return 0;
}
