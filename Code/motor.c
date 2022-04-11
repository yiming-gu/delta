#include "zf_gpio.h"
#include "hall.h"
#include "pid.h"
#include "bldc_config.h"
#include "IfxCcu6.h"
#include "ccu6_pwm.h"
#include "zf_gtm_pwm.h"
#include "move_filter.h"
#include "SEEKFREE_FUN.h"
#include "motor.h"

int16 duty = 0;           //PWM��ֵ

motor_struct motor_control;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���������ʼ��
//  @param      void
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void motor_init(void)
{
    motor_control.brake_flag = 1;   //ɲ��ʹ��
    motor_control.dir = FORWARD;                    //����Ĭ�ϵķ���
    motor_control.set_speed = 2000;
    motor_control.max_speed = BLDC_MAX_SPEED;       //���������ת�ٶ�
    motor_control.min_speed = -BLDC_MAX_SPEED;      //�������ת�ٶ�
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����A�����ţ�B������     �����ر�
//  @param      duty    ��  PWMռ�ձ�
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void mos_q1q4_open(uint16 duty)
{
    ccu6SFR->MODCTR.B.T12MODEN = 0x0b;

    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_0, duty);
    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_1, 0);
    IfxCcu6_enableShadowTransfer(ccu6SFR, TRUE, FALSE);
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����A�����ţ�C������     �����ر�
//  @param      duty    ��  PWMռ�ձ�
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void mos_q1q6_open(uint16 duty)
{
    ccu6SFR->MODCTR.B.T12MODEN = 0x23;

    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_0, duty);
    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_2, 0);
    IfxCcu6_enableShadowTransfer(ccu6SFR, TRUE, FALSE);
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����B�����ţ�A������     �����ر�
//  @param      duty    ��  PWMռ�ձ�
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void mos_q3q2_open(uint16 duty)
{
    ccu6SFR->MODCTR.B.T12MODEN = 0x0e;

    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_1, duty);
    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_0, 0);
    IfxCcu6_enableShadowTransfer(ccu6SFR, TRUE, FALSE);
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����B�����ţ�C������     �����ر�
//  @param      duty    ��  PWMռ�ձ�
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void mos_q3q6_open(uint16 duty)
{
    ccu6SFR->MODCTR.B.T12MODEN = 0x2c;

    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_1, duty);
    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_2, 0);
    IfxCcu6_enableShadowTransfer(ccu6SFR, TRUE, FALSE);
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����C�����ţ�A������     �����ر�
//  @param      duty    ��  PWMռ�ձ�
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void mos_q5q2_open(uint16 duty)
{
    ccu6SFR->MODCTR.B.T12MODEN = 0x32;

    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_2, duty);
    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_0, 0);
    IfxCcu6_enableShadowTransfer(ccu6SFR, TRUE, FALSE);
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����C�����ţ�B������     �����ر�
//  @param      duty    ��  PWMռ�ձ�
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void mos_q5q4_open(uint16 duty)
{
    ccu6SFR->MODCTR.B.T12MODEN = 0x38;

    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_2, duty);
    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_1, 0);
    IfxCcu6_enableShadowTransfer(ccu6SFR, TRUE, FALSE);
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ر��������ţ������������ţ�ʹ�������Ȧ���Ըе綯�Ƶ��������Լ����ɲ��
//  @param      void
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void mos_close(void)
{
    ccu6SFR->MODCTR.B.T12MODEN = 0x2A;
    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_0, 0);
    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_1, 0);
    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_2, 0);
    IfxCcu6_enableShadowTransfer(ccu6SFR, TRUE, FALSE);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����������
//  @param      void
//  @return     void
//  @since      ���ݼ��������Ŀ����λ������λ���
//-------------------------------------------------------------------------------------------------------------------
void motor_commutation(int8 except_hall)
{
    //ʹ�ܿ��عر�ʱ ������ζ��ر����
    if(!gpio_get(EN_PIN))
    {
        duty=0;
    }

    if(motor_control.set_speed)
    {
        if(duty)
        {
            switch(except_hall)
           {
               case 1:     mos_q1q6_open(duty);    break;
               case 2:     mos_q1q4_open(duty);    break;
               case 3:     mos_q5q4_open(duty);    break;
               case 4:     mos_q5q2_open(duty);    break;
               case 5:     mos_q3q2_open(duty);    break;
               case 6:     mos_q3q6_open(duty);    break;
               default:    mos_close();            break;
           }
        }
        else
        {
            mos_close();
        }
    }
}
