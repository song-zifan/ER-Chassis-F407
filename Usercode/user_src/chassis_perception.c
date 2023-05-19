/*
 * @Author: szf
 * @Date: 2023-02-23 19:13:13
 * @LastEditTime: 2023-03-29 22:25:16
 * @LastEditors: szf
 * @Description: 
 * @FilePath: \ER-Chassis-F407\Usercode\user_src\chassis_perception.c
 * @WeChat:szf13373959031
 */
#include "chassis_perception.h"
#include "wtr_uart.h"

/**
 * @description: 线程二：定位系统
 * @author: szf
 * @date:
 * @return {void}
 */
void ChassisPerceptionTask(void const *argument)
{
    // 码盘定位系统通过串口4收发信息
    HAL_UART_Receive_IT(&huart3, (uint8_t *)&ch, 1);

    // ADS1256_UpdateDiffData();

    // mavlink_msg_posture_send_struct(MAVLINK_COMM_0,mav_posture);

    for (;;) {
        // ADS1256_UpdateDiffData();
        osDelay(100);
    }
}

void PerceptionTaskStart()
{
    osThreadDef(perception, ChassisPerceptionTask, osPriorityNormal, 0, 512);
    osThreadCreate(osThread(perception), NULL);
}