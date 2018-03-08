#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "include.h"

//舵机PD控制 输入理想值
void ste_PD(s16 dir);

//电机PID控制 输入理想值
void mot_PID(s16 mspd);

//可调用此控制完成智能车控制,舵机占空比，电机速度
void cotrl(u16 dir,s16 mspd);

//速度检测，清零寄存器
void spd_check();

//pwm死区控制，防止溢出
void mpwm(s16 pwm);

void spwm(u16 pwm);

void contrlss(void);//控制所有



#endif// __CONTROL_H__
