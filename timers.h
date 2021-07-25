/*
 * timers.h
 *
 *
 *      Author: Bishoy Nabil
 */

#ifndef TIMERS_H_
#define TIMERS_H_

#include "micro_config.h"
#include "compiler.h"
#include "timers_registers.h"


/*****************************************************Common Configurations*********************************************************/

typedef enum
{
	INT_DISABLE,INT_ENABLE
}EN_intState_t;

typedef enum
{
	OVERFLOW,PWM,COMPARE
}EN_timerMode_t;

typedef enum
{
	DISCONNECT,TOGGLE,CLEAR_NON_INVERTING,SET_INVERTING
}EN_outputMode_t;

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}EN_clock_t;

/***********************************************Timer0,2 Configurations Structure******************************************************/

typedef struct Timer8Config
{	EN_timerMode_t mode; /*choose the timer mode*/
	EN_clock_t prescaler; /*choose the pre-scaler*/
	uint8_t initialValue; /*choose initial value*/
	uint8_t compareValue; /*choose compare value*/
	EN_outputMode_t output; /*chose the output mode*/
	EN_intState_t interrupt; /*interrupt enable/disable*/
}ST_Timer8Config_t;

/***********************************************Timer1 Configurations Structure********************************************************/
typedef enum Timer16Mode{
	OVERFLOW_16,PWM_P_8,PWM_P_9,PWM_P_10,CTC_OCR,F_PWM_8,F_PWM_9,F_PWM_10,PWM_ICR_BOTTOM,PWM_OCR_BOTTOM,
	PWM_ICR_TOP,PWM_OCR_TOP,CTC_ICR,F_PWM_ICR_BOTTOM = 14,F_PWM_OCR_BOTTOM = 15
}EN_timer16Mode_t;

typedef struct Timer16Config
{	EN_timer16Mode_t mode; /*choose the timer mode*/
	EN_clock_t prescaler; /*choose the pre-scaler*/
	unsigned short initialValue; /*choose initial value*/
	unsigned short compareValue; /*choose compare value*/
	EN_outputMode_t output; /*choose the output mode*/
	EN_intState_t interrupt; /*Enable/disable interrupt*/
}ST_Timer16Config_t;


/************************************************Timers Prototypes**********************************************************************/
void TIMER0_init(ST_Timer8Config_t* config_ptr); /*Initialise timer0*/
void TIMER0_deinit(void); /*Stop timer0*/
void TIMER1_init(const ST_Timer16Config_t* config_ptr); /*Initialise timer1*/
void TIMER1_deinit(void); /*Stop timer1*/
void TIMER2_init(ST_Timer8Config_t* config_ptr); /*Initialise timer2*/
void TIMER2_deinit(void); /*Stop timer2*/
/******************************************************Call Back Functions Prototype****************************************************/
void TIMER0_OVF_interrupt(void(*a_ptr)(void)); /*Timer0 OVERFLOW Interrupt Service Routine*/
void TIMER0_COMP_interrupt(void(*a_ptr)(void));/*Timer0 COMPARE Interrupt Service Routine*/
void TIMER1_OVF_interrupt(void(*a_ptr)(void)); /*Timer1 OVERFLOW Interrupt Service Routine*/
void TIMER1_COMPA_interrupt(void(*a_ptr)(void)); /*Timer1 COMPARE A Interrupt Service Routine*/
void TIMER1_COMPB_interrupt(void(*a_ptr)(void)); /*Timer1 COMPARE B Interrupt Service Routine*/
void TIMER2_OVF_interrupt(void(*a_ptr)(void)); /*Timer2 OVERFLOW Interrupt Service Routine*/
void TIMER2_COMP_interrupt(void(*a_ptr)(void)); /*Timer2 COMPARE Interrupt Service Routine*/

#endif /* TIMERS_H_ */
