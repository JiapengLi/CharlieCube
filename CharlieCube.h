#ifndef __CHARLIE_CUBE_H
#define __CHARLIE_CUBE_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "wiring_private.h"

typedef uint8_t u8;
typedef int8_t  s8;
typedef uint16_t u16;
typedef int16_t  s16;
typedef uint32_t u32;
typedef int32_t  s32;


/**
	PB		P0
	PC		P1
	PD		P2
	PE		P3
*/
#define CUBE_0_P			PORTA
#define CUBE_1_P			PORTA
#define CUBE_2_P			PORTC
#define CUBE_3_P			PORTC
#define CUBE_4_P			PORTF
#define CUBE_5_P			PORTF
#define CUBE_6_P			PORTK
#define CUBE_7_P			PORTK

#define CUBE_0_N			PORTC
#define CUBE_1_N			PORTF
#define CUBE_2_N			PORTF
#define CUBE_3_N			PORTK
#define CUBE_4_N			PORTA
#define CUBE_5_N			PORTK
#define CUBE_6_N			PORTA
#define CUBE_7_N			PORTC

#define CUBE_0_P_DIR		DDRA
#define CUBE_1_P_DIR		DDRA
#define CUBE_2_P_DIR		DDRC
#define CUBE_3_P_DIR		DDRC
#define CUBE_4_P_DIR		DDRF
#define CUBE_5_P_DIR		DDRF
#define CUBE_6_P_DIR		DDRK
#define CUBE_7_P_DIR		DDRK

#define CUBE_0_N_DIR		DDRC
#define CUBE_1_N_DIR		DDRF
#define CUBE_2_N_DIR		DDRF
#define CUBE_3_N_DIR		DDRK
#define CUBE_4_N_DIR		DDRA
#define CUBE_5_N_DIR		DDRK
#define CUBE_6_N_DIR		DDRA
#define CUBE_7_N_DIR		DDRC

#define CUBE_OFF()			DDRA = 0; DDRC = 0; DDRF = 0; DDRK = 0;\
							PORTA = 0; PORTC = 0; PORTF = 0; PORTK = 0;

//#define CUBE_0_ON()			DDRF = 0; DDRK = 0; PORTF = 0; PORTK = 0;
//#define CUBE_1_ON()			DDRC = 0; DDRK = 0; PORTC = 0; PORTK = 0;
//#define CUBE_2_ON()			DDRA = 0; DDRK = 0; PORTA = 0; PORTK = 0;
//#define CUBE_3_ON()			DDRA = 0; DDRF = 0; PORTA = 0; PORTF = 0;
//#define CUBE_4_ON()			DDRC = 0; DDRK = 0; PORTC = 0; PORTK = 0;
//#define CUBE_5_ON()			DDRC = 0; DDRA = 0; PORTC = 0; PORTA = 0;
//#define CUBE_6_ON()			DDRF = 0; DDRC = 0; PORTF = 0; PORTC = 0;
//#define CUBE_7_ON()			DDRA = 0; DDRF = 0; PORTA = 0; PORTF = 0;

class CUBE{
public:
	CUBE();
	void init(void);
	void scan(void);
	void write(uint8_t x, uint8_t y, uint8_t z, uint8_t val);
	void write(uint8_t layer, char c);
	void writePic8x8(uint8_t layer, uint8_t *pic);
	static CUBE *activeObject;
};

#endif