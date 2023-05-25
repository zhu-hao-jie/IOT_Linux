#include <ioCC2530.h>
#include"beep.h"
#define BEEP_PIN P0_0        //定义P0.0定义为蜂鸣器控制口

void InitBeep(void)
{
	P0DIR |= 0x01;    //P0.0定义为输出口 
	BEEP_PIN = 0;        //蜂鸣器灭
}
void BeepOn(void)
{
	P0DIR |= 0x01;
	BEEP_PIN = 1;
}
void BeepOff(void)
{
	P0DIR |= 0x01;
	BEEP_PIN = 0;
}