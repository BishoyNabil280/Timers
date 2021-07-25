/*
 * timers_registers.h
 *
 *
 *      Author: Bishoy Nabil
 */

#ifndef TIMERS_REGISTERS_H_
#define TIMERS_REGISTERS_H_

/* Timer 0 Registers */

#define TCCR0_REGISTER  *( ( volatile uint8_t* ) 0x53 )
#define TCNT0_REGISTER *( ( volatile uint8_t* ) 0x52 )
#define OCR0_REGISTER   *( ( volatile uint8_t* ) 0x5C )

/* Timer 1 Registers */

#define TCNT1H_REGISTER *( ( volatile uint8_t* ) 0x4D )
#define TCNT1L_REGISTER *( ( volatile uint8_t* ) 0x4C )
#define TCNT1_REGISTER  *( ( volatile uint16_t* ) 0x4C )
#define TCCR1A_REGISTER *( ( volatile uint8_t* ) 0x4F )
#define TCCR1B_REGISTER *( ( volatile uint8_t* ) 0x4E )
#define OCR1A_REGISTER  *( ( volatile uint16_t* ) 0x4A )
#define OCR1AH_REGISTER *( ( volatile uint8_t* ) 0x4B )
#define OCR1AL_REGISTER *( ( volatile uint8_t* ) 0x4A )
#define OCR1B_REGISTER  *( ( volatile uint16_t* ) 0x48 )
#define OCR1BH_REGISTER *( ( volatile uint8_t* ) 0x49 )
#define OCR1BL_REGISTER *( ( volatile uint8_t* ) 0x48 )
#define ICR1_REGISTER   *( ( volatile uint16_t* ) 0x46 )
#define ICR1H_REGISTER  *( ( volatile uint8_t* ) 0x47 )
#define ICR1L_REGISTER  *( ( volatile uint8_t* ) 0x46 )

/* Timer 2 Registers */

#define TCCR2_REGISTER  *( ( volatile uint8_t* ) 0x45 )
#define TCNT2_REGISTER  *( ( volatile uint8_t* ) 0x44 )
#define OCR2_REGISTER   *( ( volatile uint8_t* ) 0x43 )

#define TIMSK_REGISTER  *( ( volatile uint8_t* ) 0x59 )
#define TIFR_REGISTER   *( ( volatile uint8_t* ) 0x58 )

#endif /* TIMERS_REGISTERS_H_ */
