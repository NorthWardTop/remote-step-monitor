
#include "common.h"
#include "network.h"
#include "pedometer.h"



int main(int argc, char const *argv[])
{
    
    int sockfd = 0;
    int bytes = 0;
    unsigned int i = 0;
    struct accel acc;
    unsigned int step_conut = 0;

    struct filter_avg avg;
    struct accel filter_result;
    struct peak_val peak;
    struct slid_reg slid;
    struct time_interval differ;
    

    filter_init(&avg);
    peak_val_init(&peak);
    slid_init(&slid);
    time_init(&differ);


    sockfd = udp_create();

    //算法开始, 接受数据和处理
    for (;;) {
        
        bytes = udp_recv(sockfd, &acc);
        fprintf(stdout, "ax:%hd  ay:%hd  az:%hd  size:%d  step_count:%d\n", acc.ax, acc.ay, acc.az, bytes, step_conut);

        avg.info[i++ % FILTER_CNT] = acc; // 循环队列存入
        filter_calculate(&avg, &filter_result); //平均过滤器进行计算

        peak_val_update(&peak, &filter_result); //同时将平均过滤器过滤结果更新到峰值

        // time_cond(&differ) && space_cond(&peak, &slid)
        if (slid_update(&slid, &filter_result)) {
            if (time_cond(&differ) && space_cond(&peak, &slid)) {
                step_conut++;
                time_update(&differ); //更新上一步和这一步的时间间隔
            }
                
        }
            
        
    }
    
    
    return 0;
}
