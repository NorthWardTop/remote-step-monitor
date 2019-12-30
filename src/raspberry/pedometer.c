
#include "common.h"
#include "pedometer.h"



/**
 * 求一个样品容器内的平均
 * @filter - 样品容器
 * @sample - 返回的平均值
 */
static void filter_calculate(struct filter_avg *filter, struct accel *sample)
{
    unsigned int i;
	short x_sum = 0, y_sum = 0, z_sum = 0;
    //求一个样品容器内的平均
	for (i = 0; i < FILTER_CNT; i++) {
		x_sum += filter->info[i].ax;
		y_sum += filter->info[i].ay;
		z_sum += filter->info[i].az;
	}
	sample->ax = x_sum / FILTER_CNT;
	sample->ay = y_sum / FILTER_CNT;
	sample->az = z_sum / FILTER_CNT;
}


/**
 * 初始化峰值结构
 *      - 将最大峰值设置位最小值
 *      - 最小峰值设置位最大值, 能够准确被立即更新掉
 * @peak - 峰值结构
 */
static void peak_val_init(struct peak_val *peak)
{
    peak->new_max.ax = INT16_MIN;
    peak->new_max.ay = INT16_MIN;
    peak->new_max.az = INT16_MIN;
    // peak->old_max.ax = INT16_MIN;
    // peak->old_max.ay = INT16_MIN;
    // peak->old_max.az = INT16_MIN; 

    peak->new_min.ax = INT16_MAX;
    peak->new_min.ay = INT16_MAX;
    peak->new_min.az = INT16_MAX;
    // peak->old_min.ax = INT16_MAX;
    // peak->old_min.ay = INT16_MAX;
    // peak->old_min.az = INT16_MAX;  
}


/**
 * 更新动态峰值, SAMPLE_SIZE次更新一次清空
 * @peak - 峰值结构
 * @curr_val - 传入当前值
 */
static void peak_val_update(struct peak_val *peak, struct accel *curr_val)
{
    static unsigned int sample_cnt = 0;
    sample_cnt++;
    if (sample_cnt > SAMPLE_SIZE) {
        sample_cnt = 1;
        peak->old_max = peak->new_max;
        peak->old_min = peak->new_min;
        peak_val_init(peak);
    }

    peak->new_max.ax = max(peak->new_max.ax, curr_val->ax);
    peak->new_max.ay = max(peak->new_max.ay, curr_val->ay);
    peak->new_max.az = max(peak->new_max.az, curr_val->az);

    peak->new_min.ax = min(peak->new_min.ax, curr_val->ax);
    peak->new_min.ay = min(peak->new_min.ay, curr_val->ay);
    peak->new_min.az = min(peak->new_min.az, curr_val->az);
}


