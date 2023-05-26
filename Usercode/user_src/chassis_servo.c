#include "chassis_servo.h"
#include "user_config.h"
#include "state_management.h"
#include "can.h"
#include "wtr_can.h"
#include "chassis_servo.h"

/**
 * @description: 伺服线程
 * @author: szf
 * @return {void}
 */
void ServoTask(void const *argument)
{
    uint32_t PreviousWakeTime = osKernelSysTick();
    vTaskDelay(20);
    for (;;) {
        // 更新PID的目标值和反馈值
        xSemaphoreTakeRecursive(Chassis_control.xMutex_control,portMAX_DELAY);
        SetPIDTarget(Chassis_control.Chassis_Control_x,
                     Chassis_control.Chassis_Control_y,
                     Chassis_control.Chassis_Control_w,
                     &Chassis_pid);
        xSemaphoreGiveRecursive(Chassis_control.xMutex_control);

        xSemaphoreTakeRecursive(Chassis_position.xMutex_position,portMAX_DELAY);
        SetPIDFeedback(Chassis_position.Chassis_Position_x,
                       Chassis_position.Chassis_Position_y,
                       Chassis_position.Chassis_Position_w,
                       &Chassis_pid);
        xSemaphoreGiveRecursive(Chassis_position.xMutex_position);

        // 伺服控制
        ServoWheels(&Wheel_component);

        vTaskDelayUntil(&PreviousWakeTime, 3);
    }
}

/**
 * @description: 伺服测试线程，比赛时关掉
 * @author: szf
 * @return {void}
 */
void ServoTestTask(void const *argument)
{
    uint32_t PreviousWakeTime = osKernelSysTick();
    vTaskDelay(20);
    for (;;) {
        vTaskDelayUntil(&PreviousWakeTime, 3);
    }
}

/**
 * @description: 创建伺服线程
 * @author: szf
 * @return {void}
 */
void ServoTaskStart()
{
    osThreadDef(servo, ServoTask, osPriorityBelowNormal, 0, 512);
    osThreadCreate(osThread(servo), NULL);

    // osThreadDef(servo_test,ServoTestTask,osPriorityBelowNormal,0,512);
    // osThreadCreate(osThread(servo_test),NULL);
}

// 电机初始化
void MotorInit()
{
    CANFilterInit(&hcan1);
    hDJI[0].motorType = M2006; // 前
    hDJI[1].motorType = M2006; // 左
    hDJI[2].motorType = M2006; // 有
    hDJI[3].motorType = M2006; // claw
    hDJI[4].motorType = M2006; // 翻转
    hDJI[5].motorType = M3508; // 伸缩
    hDJI[6].motorType = M3508;
    DJI_Init(); // 大疆电机初始化
}
