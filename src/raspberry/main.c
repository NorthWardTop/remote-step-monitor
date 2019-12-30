
#include "common.h"
#include "network.h"



int main(int argc, char const *argv[])
{
    
    int sockfd = 0;
    int bytes = 0;
    struct accel acc;

    sockfd = udp_create();

    //算法开始, 接受数据和处理
    for(;;) {
       bytes = udp_recv(sockfd, &acc);
       fprintf(stdout, "ax:%hd  ay:%hd  az:%hd  size:%d\n", acc.ax, acc.ay, acc.az, bytes);

       
    }
    
    
    return 0;
}
