#ifndef __DHT11_H__
#define __DHT11_H__
#include "head.h"

extern void Delay_us(void);
extern void Delay_10us(void);
extern void Delay_ms(unsigned short Time);	//��ʱ����
extern void COM(void);                  // ��ʪд��
extern void readDHT11(void);                //��ʪ��������
extern void DATA_IO_output_Cfg(void);
extern void DATA_IO_input_Cfg(void);

extern uchar temp[2]; 
extern uchar temp1[5];
extern uchar humidity[2];
extern uchar humidity1[9];
extern uchar shidu_shi,shidu_ge,wendu_shi,wendu_ge;

#endif