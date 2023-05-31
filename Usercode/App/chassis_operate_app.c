#include "chassis_operate_app.h"
#include "semphr.h"
#include "chassis_communicate.h"
#include "chassis_machine.h"
#include "chassis_servo.h"
#include "chassis_perception.h"
#include "user_config.h"
#include "chassis_commen.h"
#include "pickup_state_machine.h"
#include "chassis_remote_control.h"
#include "wtr_uart.h"

/**
 * @description: 操作线程
 * @todo 根据各个传感器、遥控器等设计操作手操作流程
 * @return {void}
 */
void StateManagemantTask(void const *argument)
{
    vTaskDelay(20);
    for (;;) {
        JoystickControl();
        vTaskDelay(10);
    }
}

/**
 * @description: 开启线程
 * @return {void}
 */
void StateManagemantTaskStart()
{

    osThreadDef(statemanagement, StateManagemantTask, osPriorityBelowNormal, 0, 512);
    osThreadCreate(osThread(statemanagement), NULL);
}

// todo 初始化分开,封装函数
void StateInit()
{
    Chassis_component.Chassis_Point  = First_Ring;
    Chassis_component.Chassis_State  = Ready;
    Chassis_component.xMutex_chassis = xSemaphoreCreateRecursiveMutex();

    Perception_component.Perception_State  = Receive;
    Perception_component.xMutex_perception = xSemaphoreCreateRecursiveMutex();

    PIDInit();
    Chassis_pid.xMutex_pid = xSemaphoreCreateRecursiveMutex();

    Chassis_position.Chassis_Position_w = 0;
    Chassis_position.Chassis_Position_x = 0;
    Chassis_position.Chassis_Position_y = 0;
    Chassis_position.Chassis_Angle_y    = 0;
    Chassis_position.xMutex_position    = xSemaphoreCreateRecursiveMutex();

    Chassis_control.Chassis_Control_vw = 0;
    Chassis_control.Chassis_Control_vx = 0;
    Chassis_control.Chassis_Control_vy = 0;
    Chassis_control.Chassis_Control_w  = 0;
    Chassis_control.Chassis_Control_x  = 0;
    Chassis_control.Chassis_Control_y  = 0;
    Chassis_control.xMutex_control     = xSemaphoreCreateRecursiveMutex();

    Pickup_component.Pickup_Ring   = First_Ring;
    Pickup_component.Pickup_State  = Ready;
    Pickup_component.xMutex_pickup = xSemaphoreCreateRecursiveMutex();

    Wheel_component.xMutex_wheel = xSemaphoreCreateRecursiveMutex();
    Chassis_Init(Wheel_component.wheels);

    msg_joystick_send.xMutex_joystick = xSemaphoreCreateRecursiveMutex();
}

/**
 * @description: PID参数初始化
 * @return {void}
 */
void PIDInit()
{
    // 位置式pid参数设置
    Chassis_pid.Pid_pos_w.Kp    = 40;
    Chassis_pid.Pid_pos_w.Ki    = 0;
    Chassis_pid.Pid_pos_w.Kd    = 0;
    Chassis_pid.Pid_pos_w.limit = 0.5;

    Chassis_pid.Pid_pos_x.Kp    = 5;
    Chassis_pid.Pid_pos_x.Ki    = 0;
    Chassis_pid.Pid_pos_x.Kd    = 0;
    Chassis_pid.Pid_pos_x.limit = 0.5;

    Chassis_pid.Pid_pos_y.Kp    = 5;
    Chassis_pid.Pid_pos_y.Ki    = 0;
    Chassis_pid.Pid_pos_y.Kd    = 0;
    Chassis_pid.Pid_pos_y.limit = 0.5;
}

void JoystickControl()
{
    /*设计操作手的操作*/
    if (ReadJoystickSwitchs(msg_joystick_air, Left_switch)) {
        // Code for Left_switch
    }
    if (ReadJoystickSwitchs(msg_joystick_air, Right_switch)) {
        // Code for Right_switch
    }
    if (ReadJoystickButtons(msg_joystick_air, Btn_LeftCrossDown)) {
        // Code for Btn_LeftCrossDown
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_LeftCrossUp)) {
        // Code for Btn_LeftCrossUp
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_LeftCrossLeft)) {
        // Code for Btn_LeftCrossLeft
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_LeftCrossRight)) {
        // Code for Btn_LeftCrossRight
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_LeftCrossMid)) {
        // Code for Btn_LeftCrossMid
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_RightCrossUp)) {
        // Code for Btn_RightCrossUp
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_RightCrossDown)) {
        // Code for Btn_RightCrossDown
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_RightCrossLeft)) {
        // Code for Btn_RightCrossLeft
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_RightCrossRight)) {
        // Code for Btn_RightCrossRight
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_RightCrossMid)) {
        // Code for Btn_RightCrossMid
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_Btn0)) {
        // Code for Btn_Btn0
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_Btn1)) {
        // Code for Btn_Btn1
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_Btn2)) {
        // Code for Btn_Btn2
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_Btn3)) {
        // Code for Btn_Btn3
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_Btn4)) {
        // Code for Btn_Btn4
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_Btn5)) {
        // Code for Btn_Btn5
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_KnobL)) {
        // Code for Btn_KnobL
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_KnobR)) {
        // Code for Btn_KnobR
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_JoystickL)) {
        // Code for Btn_JoystickL
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_JoystickR)) {
        // Code for Btn_JoystickR
    }
}

// 
void Test_Navigation()
{
    /*测试按钮导航*/
    ChassisSwitchState(ComputerControl, &Chassis_component);

    if (ReadJoystickButtons(msg_joystick_air, Btn_LeftCrossLeft)) {
        // Code for Btn_LeftCrossLeft
        ChassisSwitchPoint(First_Point,&Chassis_component);
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_LeftCrossRight)) {
        // Code for Btn_LeftCrossRight
        ChassisSwitchPoint(Second_Point,&Chassis_component);
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_LeftCrossMid)) {
        // Code for Btn_LeftCrossMid
        ChassisSwitchPoint(Third_Point,&Chassis_component);
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_RightCrossUp)) {
        // Code for Btn_RightCrossUp
        ChassisSwitchPoint(Fourth_Point,&Chassis_component);
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_RightCrossDown)) {
        // Code for Btn_RightCrossDown
        ChassisSwitchPoint(Fifth_Point,&Chassis_component);
    }
}

void Test_RemoteControl()
{
    /*遥控器摇杆控制*/
    ChassisSwitchState(RemoteControl,&Chassis_component);
}

// todo 码盘坐标系转换函数、底盘坐标系转换函数