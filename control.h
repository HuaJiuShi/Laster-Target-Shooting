#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "include.h"

//���PD���� ��������ֵ
void ste_PD(s16 dir);

//���PID���� ��������ֵ
void mot_PID(s16 mspd);

//�ɵ��ô˿���������ܳ�����,���ռ�ձȣ�����ٶ�
void cotrl(u16 dir,s16 mspd);

//�ٶȼ�⣬����Ĵ���
void spd_check();

//pwm�������ƣ���ֹ���
void mpwm(s16 pwm);

void spwm(u16 pwm);

void contrlss(void);//��������



#endif// __CONTROL_H__
