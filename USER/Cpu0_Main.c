#include "Cpu0_Main.h"
#include "headfile.h"
#pragma section all "cpu0_dsram"


int core0_main(void)
{
	get_clk();

    hall_init();

    move_filter_init(&speed_filter);

    motor_init();

    closed_loop_pi_init();

    ccu6_pwm_init();

    pit_interrupt_ms(CCU6_0, PIT_CH0, 5);
    pit_interrupt_us(CCU6_0, PIT_CH1, 50);

	IfxCpu_emitEvent(&g_cpuSyncEvent);
	IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
	enableInterrupts();
	while (TRUE)
	{

	}
}

#pragma section all restore
