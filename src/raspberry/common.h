#ifndef __COMMON_H__
#define __COMMON_H__



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
#include <linux/limits.h>
#include <linux/kernel.h> //导入max() min()


struct accel
{
    int16_t ax, ay, az;
};

struct gyro
{
    int16_t gx, gy, gz;
};


struct raw_data {
    struct accel acc;
    struct gyro gyr;
    int16_t t;
};




#endif