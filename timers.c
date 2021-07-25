/*
 * timers.c
 *
 *
 *      Author: Bishoy Nabil
 */

#include "timers.h"

/*******************************************Pointer to Functions for Interrupt Service Routine******************************************/
static volatile void (*timer0_ovf_ptr)(void)  = NULL; /*pointer to timer0 overflow function*/
static volatile void (*timer0_comp_ptr)(void)  = NULL; /*pointer to timer0 compare function*/
static volatile void (*timer1_ovf_ptr)(void)  = NULL; /*pointer to timer1 overflow function*/
static volatile void (*timer1_compa_ptr)(void)  = NULL; /*pointer to timer1 compare a function*/
static volatile void (*timer1_compb_ptr)(void)  = NULL; /*pointer to timer1 compare b function*/
static volatile void (*timer2_ovf_ptr)(void)  = NULL; /*pointer to timer2 overflow function*/
static volatile void (*timer2_comp_ptr)(void)  = NULL; /*pointer to timer0 compare function*/

/**************************************************************ISR of Timers Interrupts***********************************************/
/*timer0 overflow ISR*/
ISR(TIMER0_OVF_vect){
	if(timer0_ovf_ptr != NULL){
		(*timer0_ovf_ptr)();
	}
}
/*timer0 compare ISR*/
ISR(TIMER0_COMP_vect){
	if(timer0_comp_ptr != NULL){
		(*timer0_comp_ptr)();
	}
}
/*timer1 overflow ISR*/
ISR(TIMER1_OVF_vect){
	if(timer1_ovf_ptr != NULL){
		(*timer1_ovf_ptr)();
	}
}
/*timer1 compare a ISR*/
ISR(TIMER1_COMPA_vect){
	if(timer1_compa_ptr != NULL){
		(*timer1_compa_ptr)();
	}
}
/*timer1 compare b ISR*/
ISR(TIMER1_COMPB_vect){
	if(timer1_compb_ptr != NULL){
		(*timer1_compb_ptr)();
	}
}

/*timer2 overflow ISR*/
ISR(TIMER2_OVF_vect){
	if(timer2_ovf_ptr != NULL){
		(*timer2_ovf_ptr)();
	}
}
/*timer2 compare ISR*/
ISR(TIMER2_COMP_vect){
	if(timer2_comp_ptr != NULL){
		(*timer2_comp_ptr)();
	}
}

/***************************************************Call Back Functions For ISR***************************************************/
/*timer0 overflow Call Back Function*/
void TIMER0_OVF_interrupt(void(*a_ptr)(void)){
	timer0_ovf_ptr = a_ptr;
}
/*timer0 compare Call Back Function*/
void TIMER0_COMP_interrupt(void(*a_ptr)(void)){
	timer0_comp_ptr = a_ptr;
}
/*timer1 overflow Call Back Function*/
void TIMER1_OVF_interrupt(void(*a_ptr)(void)){
	timer1_ovf_ptr = a_ptr;
}
/*timer1 compare a Call Back Function*/
void TIMER1_COMPA_interrupt(void(*a_ptr)(void)){
	timer1_compa_ptr = a_ptr;
}
/*timer1 compare b Call Back Function*/
void TIMER1_COMPB_interrupt(void(*a_ptr)(void)){
	timer1_compb_ptr = a_ptr;
}
/*timer2 overflow Call Back Function*/
void TIMER2_OVF_interrupt(void(*a_ptr)(void)){
	timer2_ovf_ptr = a_ptr;
}
/*timer02 compare Call Back Function*/
void TIMER2_COMP_interrupt(void(*a_ptr)(void)){
	timer2_comp_ptr = a_ptr;
}

/***********************************************************Timers Functions*********************************************************/

/***********************************************************Timer0 Initialize Function***********************************************/
void TIMER0_init(ST_Timer8Config_t* config_ptr){

	/*If the use choose overflow mode*/
	if((*config_ptr).mode == OVERFLOW){
		/*choose overflow*/
		TCCR0_REGISTER &= ~(1<<WGM00);
		TCCR0_REGISTER &= ~(1<<WGM01);
		/*choose pre-scaler*/
		TCCR0_REGISTER |= (TCCR0_REGISTER & 0xF8) | ((*config_ptr).prescaler);
		/*choose initial value*/
		TCNT0_REGISTER = (*config_ptr).initialValue;
		/*Enable Interrupt*/
		if((*config_ptr).interrupt == INT_ENABLE){
			TIMSK_REGISTER = (1<<TOIE0);
			/* Global Interrupt Enable */
			SREG|=(1<<7);
		}
	}
	/*if the use choose compare mode*/
	else if((*config_ptr).mode == COMPARE)
	{
		/*choose compare mood*/
		TCCR0_REGISTER = (1<<WGM01);
		/*choose from DISCONNECT, TOGGLE, CLEAR, SET*/
		TCCR0_REGISTER = (TCCR0_REGISTER & 0xCF) | (((*config_ptr).output)<<4);
		/*choose pre-scaler*/
		TCCR0_REGISTER |= (TCCR0_REGISTER & 0xF8) | ((*config_ptr).prescaler);
		/*choose initial value*/
		TCNT0_REGISTER = (*config_ptr).initialValue;
		/*choose compare value*/
		OCR0_REGISTER = (*config_ptr).compareValue;
		/*Enable Interrupt*/
		if((*config_ptr).interrupt == INT_ENABLE){
			TIMSK_REGISTER = (1<<OCIE0);
			/* Global Interrupt Enable */
			SREG|=(1<<7);
		}
	}
	else if((*config_ptr).mode == PWM){
		/*choose PWM mood*/
		TCCR0_REGISTER |= (1<<WGM00) | (1<<WGM01);
		/*choose from DISCONNECT,NON_INVERTING,NVERTING*/
		TCCR0_REGISTER = (TCCR0_REGISTER & 0xCF) | (((*config_ptr).output)<<4);
		/*choose pre-scaler*/
		TCCR0_REGISTER |= (TCCR0_REGISTER & 0xF8) | ((*config_ptr).prescaler);
		/*choose initial value*/
		TCNT0_REGISTER = (*config_ptr).initialValue;
		/*choose compare value*/
		OCR0_REGISTER = (*config_ptr).compareValue;
		/*Enable Interrupt*/
		if((*config_ptr).interrupt == INT_ENABLE){
			TIMSK_REGISTER = (1<<OCIE0);
			/* Global Interrupt Enable */
			SREG|=(1<<7);
		}
	}
}

/**********************************************************Timer0 Stop Function*******************************************************/
void TIMER0_deinit(void){
	/*Timer stop*/
	TCCR0_REGISTER = 0;
}

/***********************************************************Timer2 Initialise Function***********************************************/
void TIMER2_init(ST_Timer8Config_t* config_ptr){
	/*If the use choose overflow mode*/
	if((*config_ptr).mode == OVERFLOW){
		/*choose overflow*/
		TCCR2_REGISTER &= ~(1<<WGM20);
		TCCR2_REGISTER &= ~(1<<WGM21);
		/*choose pre-scaler*/
		TCCR2_REGISTER |= (TCCR2_REGISTER & 0xF8) | ((*config_ptr).prescaler);
		/*choose initial value*/
		TCNT2_REGISTER = (*config_ptr).initialValue;
		/*Enable Interrupt*/
		if((*config_ptr).interrupt == INT_ENABLE){
			TIMSK_REGISTER = (1<<TOIE2);
			/* Global Interrupt Enable */
			SREG|=(1<<7);
		}
	}
	/*if the use choose compare mode*/
	else if((*config_ptr).mode == COMPARE)
	{
		/*choose compare mood*/
		TCCR2_REGISTER = (1<<WGM21);
		/*choose from DISCONNECT, TOGGLE, CLEAR, SET*/
		TCCR2_REGISTER = (TCCR2_REGISTER & 0xCF) | (((*config_ptr).output)<<4);
		/*choose pre-scaler*/
		TCCR2_REGISTER |= (TCCR2_REGISTER & 0xF8) | ((*config_ptr).prescaler);
		/*choose initial value*/
		TCNT2_REGISTER = (*config_ptr).initialValue;
		/*choose compare value*/
		OCR2_REGISTER = (*config_ptr).compareValue;
		/*Enable Interrupt*/
		if((*config_ptr).interrupt == INT_ENABLE){
			TIMSK_REGISTER = (1<<OCIE2);
			/* Global Interrupt Enable */
			SREG|=(1<<7);
		}
	}
	else if((*config_ptr).mode == PWM){
		/*choose PWM mood*/
		TCCR2_REGISTER |= (1<<WGM20) | (1<<WGM21);
		/*choose from DISCONNECT,NON_INVERTING,NVERTING*/
		TCCR2_REGISTER = (TCCR2_REGISTER & 0xCF) | (((*config_ptr).output)<<4);
		/*choose pre-scaler*/
		TCCR2_REGISTER |= (TCCR2_REGISTER & 0xF8) | ((*config_ptr).prescaler);
		/*choose initial value*/
		TCNT2_REGISTER = (*config_ptr).initialValue;
		/*choose compare value*/
		OCR2_REGISTER = (*config_ptr).compareValue;
		/*Enable Interrupt*/
		if((*config_ptr).interrupt == INT_ENABLE){
			TIMSK_REGISTER = (1<<OCIE2);
			/* Global Interrupt Enable */
			SREG|=(1<<7);
		}
	}
}

/**********************************************************Timer2 Stop Function*******************************************************/
void TIMER2_deinit(void){
	/*Timer stop*/
	TCCR2_REGISTER = 0;
}

/***********************************************************Timer1 Initialise Function***********************************************/
void TIMER1_init(const ST_Timer16Config_t* config_ptr){
	if((*config_ptr).mode == OVERFLOW_16){
		/*choose overflow mode*/
		TCCR1A_REGISTER = (*config_ptr).mode;
		TCCR1B_REGISTER = (*config_ptr).mode;
		/*set HIGH with non-WM mode*/
		TCCR1A_REGISTER |= (1<<FOC1A) | (1<<FOC1B);
		/*Enable Overflow Interrupt*/
		if((*config_ptr).interrupt == INT_ENABLE){
			TIMSK_REGISTER |= (1<<TOIE1);
			/* Global Interrupt Enable */
			SREG|=(1<<7);
		}
	}else if(((*config_ptr).mode == PWM_P_8) || ((*config_ptr).mode == PWM_P_9) || ((*config_ptr).mode == PWM_P_10)
			|| ((*config_ptr).mode == F_PWM_8) || ((*config_ptr).mode == F_PWM_9) || ((*config_ptr).mode == F_PWM_10)
			|| ((*config_ptr).mode == PWM_ICR_BOTTOM) || ((*config_ptr).mode == PWM_OCR_BOTTOM) || ((*config_ptr).mode == PWM_ICR_TOP)
			|| ((*config_ptr).mode == PWM_OCR_TOP) || ((*config_ptr).mode == F_PWM_ICR_BOTTOM) || ((*config_ptr).mode == F_PWM_OCR_BOTTOM)){
		/*choose overflow mode*/
		TCCR1A_REGISTER = ((*config_ptr).mode & 0x03);
		TCCR1B_REGISTER = (((*config_ptr).mode & 0x0C)<<1);
		/*set LOW for PWM mode*/
		TCCR1A_REGISTER &= ~((1<<FOC1A) | (1<<FOC1B));
		/*Enable Interrupt*/
		if((*config_ptr).interrupt == INT_ENABLE){
			TIMSK_REGISTER |= (1<<OCIE1A);
			TIMSK_REGISTER |= (1<<OCIE1B);
			/* Global Interrupt Enable */
			SREG|=(1<<7);
		}
	}
	else if(((*config_ptr).mode == CTC_OCR) || ((*config_ptr).mode == CTC_ICR)){
		/*choose overflow mode*/
		TCCR1A_REGISTER = ((*config_ptr).mode & 0x03);
		TCCR1B_REGISTER = (((*config_ptr).mode & 0x0C)<<1);
		/*set HIGH with non-WM mode*/
		TCCR1A_REGISTER |= (1<<FOC1A) | (1<<FOC1B);
		/*Enable Interrupt*/
		if((*config_ptr).interrupt == INT_ENABLE){
			TIMSK_REGISTER |= (1<<OCIE1A);
			TIMSK_REGISTER |= (1<<OCIE1B);
			/* Global Interrupt Enable */
			SREG|=(1<<7);
		}
	}
	/*set compare output mode*/
	TCCR1A_REGISTER = (TCCR1A_REGISTER & 0x0F) | ((*config_ptr).output<<4);
	TCCR1A_REGISTER = (TCCR1A_REGISTER & 0x0F) | ((*config_ptr).output<<6);
	/*set pre-scaler*/
	TCCR1B_REGISTER = (TCCR1B_REGISTER & 0xF8) | (*config_ptr).prescaler;
	/*set initial value*/
	TCNT1_REGISTER = (*config_ptr).initialValue;
	/*set compare value*/
	OCR1A_REGISTER = (*config_ptr).compareValue;
}

/**********************************************************Timer1 Stop Function*******************************************************/
void TIMER1_deinit(void){
	/*Timer stop*/
	TCCR1A_REGISTER = 0;
	TCCR1B_REGISTER = 0;
	TCNT1_REGISTER = 0;
	OCR1A_REGISTER = 0;
	OCR1B_REGISTER = 0;
	TIMSK_REGISTER &= ~(1<<TOIE1);
}

