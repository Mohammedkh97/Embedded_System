

#ifndef TIMERS_H_
#define TIMERS_H_

#include "stdTypes.h"
#include "Utils.h"
#include "MemoryMap.h"

typedef enum{
	TIMER0_STOP=0,
	TIMER0_SCALER_1,
	TIMER0_SCALER_8,
	TIMER0_SCALER_64,
	TIMER0_SCALER_256,
	TIMER0_SCALER_1024,
	EXTERNALl_FALLING,
	EXTERNAL_RISING
}Timer0Scaler_t;

typedef enum
{
	TIMER0_NORMAL_MODE=0,
	TIMER0_PHASECORRECT_MODE,
	TIMER0_CTC_MODE,
	TIMER0_FASTPWM_MODE

}Timer0Mode_t;


typedef enum
{
	OC0_DISCONNECTED=0,
	OC0_TOGGLE,
	OC0_NON_INVERTING,
	OC0_INVERTING

}OC0Mode_t;

void TIMER0_Init(Timer0Mode_t mode,Timer0Scaler_t scaler);

void TIMER0_OC0Mode(OC0Mode_t mode);
void TIMER0_OV_InterruptEnable(void);
void TIMER0_OV_InterruptDisable(void);
void TIMER0_OC_InterruptEnable(void);
void TIMER0_OC_InterruptDisable(void);
void TIMER0_OV_SetCallBack(void(*local_fptr)(void));

/*********************************************************************************************************/

typedef enum{
	TIMER1_STOP=0,
	TIMER1_SCALER_1,
	TIMER1_SCALER_8,
	TIMER1_SCALER_64,
	TIMER1_SCALER_256,
	TIMER1_SCALER_1024,
	EXTERNAL0_FALLING,
	EXTERNAL0_RISING
}Timer1Scaler_t;

typedef enum
{
	TIMER1_NORMAL_MODE=0,
	TIMER1_CTC_ICR_TOP_MODE,
	TIMER1_CTC_OCRA_TOP_MODE,
	TIMER1_FASTPWM_ICR_TOP_MODE,
	TIMER1_FASTPWM_OCRA_TOP_MODE

}Timer1Mode_t;

typedef enum
{
	OCRA_DISCONNECTED=0,
	OCRA_TOGGLE,
	OCRA_NON_INVERTING,
	OCRA_INVERTING

}OC1A_Mode_t;

typedef enum
{
	OCRB_DISCONNECTED=0,
	OCRB_TOGGLE,
	OCRB_NON_INVERTING,
	OCRB_INVERTING

}OC1B_Mode_t;


typedef enum{
	RISING,
	FALLING
}ICU_Edge_t;




void Timer1_InputCaptureEdge(ICU_Edge_t edge);
void Timer1_Init( Timer1Mode_t mode,Timer1Scaler_t scaler);
void Timer1_OCRA1Mode(OC1A_Mode_t oc1a_mode);
void Timer1_OCRB1Mode(OC1B_Mode_t oc1b_mode);


void Timer1_ICU_InterruptEnable(void);
void Timer1_ICU_InterruptDisable(void);

void Timer1_OVF_InterruptEnable(void);
void Timer1_OVF_InterruptDisable(void);

void Timer1_OCA_InterruptEnable(void);
void Timer1_OCA_InterruptDisable(void);

void Timer1_OCB_InterruptEnable(void);
void Timer1_OCB_InterruptDisable(void);

void Timer1_OVF_SetCallBack(void(*LocalFptr)(void));
void Timer1_OCA_SetCallBack(void(*LocalFptr)(void));
void Timer1_OCB_SetCallBack(void(*LocalFptr)(void));
void Timer1_ICU_SetCallBack(void(*LocalFptr)(void));

#endif /* TIMERS_H_ */