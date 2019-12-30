#ifndef __PEDOMETER_H__
#define __PEDOMETER_H__


#include "common.h"

// 均值滤波器容器大小
#define FILTER_CNT              4
// 动态峰值样品容器大小
#define SAMPLE_SIZE             50
// 动态精度 两次变化差的绝对值决定是否更新
#define DYNAMIC_PRECISION       30

// 平均滤波器容器
struct filter_avg {
	struct accel info[FILTER_CNT];
	unsigned char count;
};


//峰值结构, 存储上一个峰值和新峰值
struct peak_val {
    struct accel new_max, new_min;
    struct accel old_max, old_min;
};


// 一个线性移位寄存器，用于过滤高频噪声
struct slid_reg {
    struct accel new_sample;
    struct accel old_sample;
};






#endif