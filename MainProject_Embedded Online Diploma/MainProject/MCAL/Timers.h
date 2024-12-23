

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
	TIMER0_Prescaller_FalExtClk,
	TIMER0_Prescaller_RaisExtClk
}Timer0Scaler_t;

typedef enum
{
	TIMER0_NORMAL_MODE=0,
	TIMER0_PHASECORRECT_MODE,
	TIMER0_CTC_MODE,
	TIMER0_FASTPWM_MODE

}Timer0Mode_t;

/* Output Compare Modes - non PWM modes */
typedef enum
{
	OC0_DISCONNECTED=0,
	OC0_TOGGLE,
	OC0_CLEAR,          // OC0_INVERTING,
	OC0_SET           //  OC0_NON_INVERTING

}OC0_non_PWM_Mode_t;


/* Output Compare Modes - PWM modes */
typedef enum
{
	OC0_PWM_DISCONNECTED=0,
	OC0_PWM_RESERVED,
	OC0_PWM_CLEAR,          // OC0_INVERTING,
	OC0_PWM_SET           //  OC0_NON_INVERTING
}OC0_PWM_Mode_t;

/* Output Compare Modes - Phase Correct Mode modes */
typedef enum
{
	OC0_Phase_Correct_DISCONNECTED=0,
	OC0_Phase_Correct_RESERVED,
	OC0_Phase_Correct_CLEAR,          // OC0_INVERTING,
	OC0_Phase_Correct_SET           //  OC0_NON_INVERTING
}OC0_Phase_Correct_Mode_t;

void TIMER0_Init(Timer0Mode_t OC0_Mode,Timer0Scaler_t scaler);
void TIMER0_OC0_non_PWM_Mode(OC0_non_PWM_Mode_t OC0_non_PWM_Mode);
void TIMER0_OC0_PWM_Mode(OC0_PWM_Mode_t OC0_PWM_Mode);
void TIMER0_OC0_Phase_Correct_Mode(OC0_Phase_Correct_Mode_t OC0_Phase_Correct_Mode);
void TIMER0_Set_OCR0_Value(u8 Value);
void TIMER0_SetDesiredTime_ms (u32 time_ms);
void TIMER0_SetDesiredTime_us (u32 time_us);
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
	TIMER1_Prescaller_FallingExtClk,
	TIMER1_Prescaller_RaisingExtClk
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
	OCRA_CLEAR,
	OCRA_SET

}OC1A_Mode_t;

typedef enum
{
	OCRB_DISCONNECTED=0,
	OCRB_TOGGLE,
	OCRB_CLEAR,
	OCRB_SET
}OC1B_Mode_t;


typedef enum{
	RISING,
	FALLING
}ICU_Edge_t;

/************************************************************************/
/* TIMER_2                                                                     */
/************************************************************************/
 typedef enum
 {
	TIMER2_Stop = 0,
	TIMER2_SCALER_1,
	TIMER2_SCALER_8,
	TIMER2_SCALER_64,
	TIMER2_SCALER_256,
	TIMER2_SCALER_1024,
	TIMER2_Prescaller_FallingExtClk,
	TIMER2_Prescaller_RaisingExtClk
	 
}Timer2Scaler_t;


typedef enum
{
	TIMER2_NORMAL_MODE=0,
	TIMER2_PHASECORRECT_MODE,
	TIMER2_CTC_MODE,
	TIMER2_FASTPWM_MODE
	
}Timer2Mode_t;

/* Output Compare Modes - non PWM modes */
typedef enum
{
	OC2_DISCONNECTED=0,
	OC2_TOGGLE,
	OC2_NON_INVERTING,  // OC0_CLEAR,
	OC2_INVERTING		// OC0_SET,
}OC2_Non_PWM_Mode_t;


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

void TIMER0_SetOCR0_Value	  (u8 Value);
void TIMER0_SetCompareMatchValue(u8 Value);
void TIMER0_SetDesiredTime_ms (u32 time_ms);
void TIMER0_SetDesiredTime_us (u32 time_us);
void Timer1_Set_ICR1_Value(u16 value);

#endif /* TIMERS_H_ */