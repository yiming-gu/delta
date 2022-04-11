#ifndef _PID_H
#define _PID_H

#include "common.h"

typedef struct
{
    float kp;           //PI�ջ��ı�������
    float ki;           //PI�ջ��Ļ��ֲ���
    int32 target_speed; //�ջ���Ŀ���ٶ� ��Ҫֱ���޸��������
    int32 real_speed;   //��ǰ���ת��
    int32 error;        //Ŀ���ٶ���ʵ���ٶ����
    int32 out_max;      //�ջ�������
    int32 pout;         //�ջ����ֵ
    float iout;         //�ջ����ֵ
    int32 out;          //�ջ����ֵ
}closed_loop_struct;



extern closed_loop_struct closed_loop;
//int16 closed_loop_pi_calc(float pek); //PID�������
void closed_loop_pi_init(void); //PI��ʼ������
int32 closed_loop_pi_calc(int32 read_error); //PI�������
#endif
