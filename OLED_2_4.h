//!
//! @file OLED_2_4.h,v
//!
//! Copyright (c) 2011 HB-Best Weinheim
//!
//! @version 1.0 $Id: MS5541.c,v 1.0
//!
//! @todo

//_____ I N C L U D E S

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>

#define NOP()		asm("nop")
#define Longnop() 	{NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();}

#define BLACK 	0x0000
#define GREEN 	0x0780
#define RED	  	0xF800
#define BLUE  	0x008F
#define YELLOW	0xFF80

unsigned long get_seconds();

void S6e63d6_Init(void);

void S6e63d6_FillGram(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void S6e63d6_FillGramWH(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t color);

void S6e63d6_SetScreenXY(uint16_t x, uint16_t y);
void S6e63d6_SetGramAddr(uint16_t Addr);
void S6e63d6_SetWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void S6e63d6_ClrScreen(uint16_t color);

void S6e63d6_print_char(uint16_t x, uint16_t y, char asciicode, uint8_t scale, uint16_t fcolor, uint16_t bcolor);
void S6e63d6_print_string(uint16_t x, uint16_t y, char *data_s, uint8_t scale, uint16_t fcolor, uint16_t bcolor);

void S6e63d6_print_int(uint16_t x, uint16_t y, unsigned int num, uint8_t ges, uint8_t scale, uint16_t fcolor );
void S6e63d6_print_int0(uint16_t x, uint16_t y, unsigned int num, uint8_t ges, uint8_t scale, uint16_t fcolor );
void S6e63d6_putf(uint16_t x, uint16_t y, float zahl, int sges, int snach, uint8_t scale, uint16_t fcolor);
void S6e63d6_putf_2(uint16_t x, uint16_t y, float zahl, int sges, int snach, uint8_t scale, uint16_t fcolor);

// Hardware connection
/*
OLED Display			XMega Controller
DATA0-7			->		PortB
CSB   			-> 		PA4
E	 			-> 		PA6
RS  			-> 		PA5
RW  			-> 		PA7
OL_BOOST		->		PE5  (nicht TC PC2 !)
*/

#define CSB_H()   (PORTA.OUT |= 0x10)  // 1
#define CSB_L()   (PORTA.OUT &= ~0x10)

#define E_H()  (PORTA.OUT |= 0x40)   // 1
#define E_L()  (PORTA.OUT &= ~0x40)

#define RS_Com() (PORTA.OUT &= ~0x20)
#define RS_Dat() (PORTA.OUT |= 0x20)   // 1

#define Read()  (PORTA.OUT |= 0x80)  // 1
#define Write()  (PORTA.OUT &= ~0x80)

#define OL_Boost_ON()  (PORTE.OUT |= 0x20)   // 1
#define OL_Boost_OFF()  (PORTE.OUT &= ~0x20)

