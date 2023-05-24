/**
 * @Author: szf
 * @Date: 2023-02-22 10:59:01
 * @LastEditTime: 2023-02-22 19:27:40
 * @LastEditors: szf
 * @Description: ER
 * @FilePath: \ER\Usercode\user_src\user_main.c
 * @WeChat:szf13373959031
 **/

#include "user_main.h"
#include "wtr_dji.h"
#include "wtr_can.h"
#include "wtr_uart.h"
#include "wtr_mavlink.h"
#include "state_management.h"
#include "wtr_ads1256.h"
#include "chassis_communicate.h"
#include "chassis_machine.h"
#include "chassis_servo.h"
#include "chassis_perception.h"

/**
 * @description: 初始化与开启线程
 * @author: szf
 * @date:
 * @return {void}
 */
void StartDefaultTask(void const *argument)
{
    /*初始化*/
    StateInit();
    MotorInit();       // 电机初始化
    CommunicateInit(); // 通信初始化
    PercerptionInit(); // 定位初始化

    /*开启线程*/
    PerceptionTaskStart(&ControllerData); // 底盘感知定位线程
    ChassisTaskStart(&ControllerData);    // 舵轮底盘线程
    ServoTaskStart();                     // 伺服线程
    CommunicateStart();                   // 通信线程
    StateManagemantTaskStart();           // 切换状态线程

    for (;;) {
        osDelay(1);
    }
}
