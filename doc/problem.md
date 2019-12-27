
## 问题1: 解决使用DMP库的远程I2C设备的读写问题(DMP不含远程socket读写I2C功能)
### 问题: 由于DMP库只有针对本地I2C设备的操作, 无法针对远程socket设备读写

### 方案1: 重定向I2C设备描述符到socket
    在NodeMCU端, 通过网路TCP/UDP收到的每字节消息, 同步读写到I2C接口, 也就是读写MPU6050设备
    在raspberrypi端, 通过虚拟一个I2C设备, 并将虚拟I2C设备重定向到socket即可实现
      那么对虚拟I2C设备的读写就相当于对socket的读写
      再启动一个进程, 正常使用DMP库, 但操作的是I2C虚拟设备

### 方案2: 不使用DMP库, 自己在树莓派端实现算法
    https://blog.csdn.net/Dancer__Sky/article/details/81504778
    https://cdc.tencent.com/2013/07/26/%e5%88%a9%e7%94%a8%e4%b8%89%e8%bd%b4%e5%8a%a0%e9%80%9f%e5%99%a8%e7%9a%84%e8%ae%a1%e6%ad%a5%e6%b5%8b%e7%ae%97%e6%96%b9%e6%b3%95/

