//!
//! @file OLED_2_4.c,v
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
#include <string.h>
#include "OLED_2_4.h"
#include "OLED_2_4_FN12x8.h"



//----------------------------------------------------------------
void S6e63d6_WriteCmd(uint8_t data)
{
	CSB_H();
    Write();
	RS_Com();
//	NOP();
	CSB_L();
//	NOP();
	E_H();
    PORTB.OUT = 0x00;
	NOP();
	E_L();
//	NOP();
	E_H();
    PORTB.OUT = data;
	NOP();
	E_L();
//	NOP();
	CSB_H();
    Read();
	RS_Dat();
}

//----------------------------------------------------------------
void S6e63d6_WriteData(uint16_t data)
{
	CSB_H();
	Write();
    RS_Dat();
//   	NOP();
	CSB_L();
//	NOP();
	E_H();
    PORTB.OUT = (unsigned char)( data>>8 ) ;
	NOP();
	E_L();
//	NOP();
	E_H();
    PORTB.OUT = (unsigned char)(data&0xFF);
//	NOP();
	E_L();;
	NOP();
	CSB_H();
    Read();
	RS_Dat();
}

void S6e63d6_Init(void)
{
	
	PORTB.OUT |= 0xFF;
	PORTB.DIRSET = 0xFF;
	PORTA.DIRSET = 0xF0;  	// Oberen 4 bits output
	PORTA.OUT |= 0xF0;  	// erst mal alles hight
	PORTE.DIRSET = 0x20;  	// Bosster EN bit
	OL_Boost_OFF();  		// erst mal aus
   
    //gamma setting 100 nits, for 2.8" display
//    Hyc_drvLcd_WriteInstruct(0x70);
//    Hyc_drvLcd_WriteData(0x1900);// Gamma Top/Bottom R
//    Hyc_drvLcd_WriteInstruct(0x71);
//    Hyc_drvLcd_WriteData(0x1b00);// Gamma Top/Bottom G
//    Hyc_drvLcd_WriteInstruct(0x72);
//    Hyc_drvLcd_WriteData(0x2600);// Gamma Top/Bottom B
//    Hyc_drvLcd_WriteInstruct(0x73);
//    Hyc_drvLcd_WriteData(0x0813);// Gamma Top Bottom R1,2
//    Hyc_drvLcd_WriteInstruct(0x74);
//    Hyc_drvLcd_WriteData(0x1e11);// Gamma Top Bottom R3,4
//    Hyc_drvLcd_WriteInstruct(0x75);
//    Hyc_drvLcd_WriteData(0x2717);// Gamma Top Bottom G1,2
//    Hyc_drvLcd_WriteInstruct(0x76);
//    Hyc_drvLcd_WriteData(0x1915);// Gamma Top Bottom G3,4
//    Hyc_drvLcd_WriteInstruct(0x77);
//    Hyc_drvLcd_WriteData(0x231b);// Gamma Top Bottom B1,2
//    Hyc_drvLcd_WriteInstruct(0x78);
//    Hyc_drvLcd_WriteData(0x2116);// Gamma Top Bottom B3,4


	S6e63d6_WriteCmd(0x24);	// 8bit Interface !
	
    S6e63d6_WriteCmd(0x03);

//////////////////////////////////////////////////////////////////////////
/// Setzt Bildschirm   0,0 >>>>>>>>>>>>>>>>>>>>>|
//                      |                       |
//                     0,239 >>>>>>>>>>>>>> 319,239
//

    S6e63d6_WriteData(0x0031);//65K color,88RGB, Horizontal scanning at first
//    S6e63d6_WriteData(0x0030);//65K color,88RGB, Horizontal scanning at first

	S6e63d6_WriteCmd(0x06);
	S6e63d6_WriteData(0x0010);  // 8 Color Mode (3bit)

	S6e63d6_WriteCmd(0x10);
	S6e63d6_WriteData(0x0000);
	
	S6e63d6_WriteCmd(0x18);
	S6e63d6_WriteData(0x0028);

	S6e63d6_WriteCmd(0xf8);	      //VGH Setting
	S6e63d6_WriteData(0x000F);

	S6e63d6_WriteCmd(0xf9);	      //VGL Setting
	S6e63d6_WriteData(0x000F);

    S6e63d6_WriteCmd(0x20);
    S6e63d6_WriteData(0x00ef);//240
    S6e63d6_WriteCmd(0x21);
    S6e63d6_WriteData(0x013f);//320


	S6e63d6_WriteCmd(0x05);   // Display on
	S6e63d6_WriteData(0x0001);

	S6e63d6_ClrScreen(0x0);   // Cls

	// Must be after CLS, because of to much current from the Display

	OL_Boost_ON();  // dann Hell

}

void S6e63d6_ClrScreen(uint16_t color) 
{ 
    uint16_t m,n;
    S6e63d6_SetWindow(0, 0, 319, 239);  
    S6e63d6_SetGramAddr(0);             // set GRAM address
	S6e63d6_WriteCmd(0x22);           // write GRAM command

    for(m=0;m<320;m++)
    for(n=0;n<240;n++)
    {
        S6e63d6_WriteData (color);
    }

}

void S6e63d6_SetWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    uint16_t tmp;
    
    if(x1>x2){tmp = x1; x1 = x2; x2 = tmp;}
    if(y1>y2){tmp = y1; y1 = y2; y2 = tmp;}

    S6e63d6_WriteCmd(0x35);             // Set StartX
    S6e63d6_WriteData(x1 & 0x01ff);
    S6e63d6_WriteCmd(0x36);             // Set EndX
    S6e63d6_WriteData(x2 & 0x01ff);
    S6e63d6_WriteCmd(0x37);             // Set StartY and EndY
    S6e63d6_WriteData((y1 << 8) | (y2 & 0x00ff));

}

void S6e63d6_SetGramAddr(uint16_t Addr)
{
    S6e63d6_WriteCmd(0x20);             // write low nibble of GRAM address (Bit 0-7)
    S6e63d6_WriteData(Addr & 0x00ff);
    S6e63d6_WriteCmd(0x21);             //write high nibble of GRAM address (Bit 8-15)
    S6e63d6_WriteData((Addr>>8) & 0x01ff);
}


void S6e63d6_SetScreenXY(uint16_t x, uint16_t y)
{
//    S6e63d6_SetGramAddr((x*0x100)+(y%0x100)); 
    S6e63d6_WriteCmd(0x20);             // write low nibble of GRAM address (Bit 0-7)
    S6e63d6_WriteData(y & 0x00ff);
    S6e63d6_WriteCmd(0x21);             //write high nibble of GRAM address (Bit 8-15)
    S6e63d6_WriteData(x & 0x01ff);
}

//////////////////////////////////////////////////////////////////////////
/// Füllt Gram im Rechteck x1,y1 -----------------,
//                            |                   |
//                            >---------------- w,h
//


void S6e63d6_FillGramWH(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t color)
{
    S6e63d6_FillGram(x1, y1, x1+w-1, y1+h-1, color);    
}

//////////////////////////////////////////////////////////////////////////
/// Füllt Gram im Rechteck x1,y1 -----------------,
//                            |                   |
//                            >----------------x2,y2
//

void S6e63d6_FillGram(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    uint16_t Size;

    if(x1>x2){Size = x1; x1 = x2; x2 = Size;}
    if(y1>y2){Size = y1; y1 = y2; y2 = Size;}
    Size = (x2-x1+1)*(y2-y1+1);

    S6e63d6_SetWindow(x1, y1, x2, y2);  
    S6e63d6_SetScreenXY(x1, y1);        
	S6e63d6_WriteCmd(0x22);           
    while(Size-- != 0)
    {
        S6e63d6_WriteData(color);

    }

}

// Ein Zeichen des Zeichenssatzes an x-y-Koordinate auf dem LCD ausgeben um
// den Faktor "scale" skaliert
void S6e63d6_print_char(uint16_t x, uint16_t y, char asciicode, uint8_t scale, uint16_t fcolor, uint16_t bcolor)
{
    int t1;
	int xp;
    int  t2, t3, t4, t5;
	uint8_t xscale;
    unsigned char ch;
   
    ch = 0;

    //Postion des Zeichens in der Lookup-Tabelle
    //finden
    t1 = 0;
    while(t1 < MAXCHARS)
    {
        if(arraypos[t1] == asciicode)
        {
            ch = t1 + 1;
            t1 = MAXCHARS;
        }
        t1++;
    }

	if (scale > 1) xscale = scale -1;
	else xscale = scale;

	S6e63d6_SetWindow(x, y, x + xscale * 8 - 1, y + scale * 12 - 1);


    //Zeichen in Bits zerlegen
    for(t1 = (ch - 1) * 12; t1 < ch * 12; t1++)
    {
        for(t5 = 0; t5 < scale; t5++)
        {
			S6e63d6_SetScreenXY(x, y++);
			S6e63d6_WriteCmd(0x22);           // write GRAM - Data command Start
            for(t2 = 7; t2 >= 0; t2--)
            {

                xp = 1;
                for(t3 = 0; t3 < t2; t3++)
                {
                    xp <<= 1;
                }  
                
                for(t4 = 0; t4 < xscale; t4++)
                {
                    if( pgm_read_byte(&fchar[t1]) & (int) xp)
                    {
                    	S6e63d6_WriteData (fcolor);
                    }     
                    else
                    {
                    	S6e63d6_WriteData (bcolor);
                    }
                }    
            }
			S6e63d6_WriteCmd(0x00);           // write GRAM - Data command End 
        }    
    }

}

void S6e63d6_print_string(uint16_t x, uint16_t y, char *data_s, uint8_t scale, uint16_t fcolor, uint16_t bcolor)
{
	uint16_t xscale=scale;
	if (scale > 1) xscale--;
	while(*data_s)
	{
		if(x <= 320)
		{
			S6e63d6_print_char(x, y, *data_s, scale, fcolor, bcolor); // display a character at point (x,y)
			x = x + 8 * xscale;
			data_s++;
		}
	}
}


//--------------------------------------------------------------------
void S6e63d6_print_int(uint16_t x, uint16_t y, unsigned int num, uint8_t ges, uint8_t scale, uint16_t fcolor )
{
	char buffer[10];
	uint8_t z;
	uint8_t xscale=scale;
	if (scale > 1) xscale--;
	for (z=0;z<10;z++) buffer[z]=0;
    sprintf(buffer, "%u", num);
	
	if ((num < 100) && (ges == 3))
	{
		S6e63d6_print_char(x, y, ' ', scale, fcolor, BLACK); // display a space at point (x,y)
		x = x + 8 * xscale;
	}
	if ((num < 10) && (ges >= 2))
	{
		S6e63d6_print_char(x, y, ' ', scale, fcolor, BLACK); // display a space at point (x,y)
		x = x + 8 * xscale;
	}

	S6e63d6_print_string(x, y, (unsigned char *) buffer, scale, fcolor, BLACK);
}

void S6e63d6_print_int0(uint16_t x, uint16_t y, unsigned int num, uint8_t ges, uint8_t scale, uint16_t fcolor )
{
	char buffer[10];
	uint8_t z, l;
	for (z=0;z<10;z++) buffer[z]=0;
    sprintf(buffer, "%u", num);
	l=strlen(buffer);
	if (l < ges)
	{
		for(z=ges; z>0; z--) buffer[z] = buffer[z-1];
		for(z=0; z < (ges-l); z++) buffer[z]='0';
	}	
	S6e63d6_print_string(x, y, (unsigned char *) buffer, scale, fcolor, BLACK);
}


void S6e63d6_putf(uint16_t x, uint16_t y, float zahl, int sges, int snach, uint8_t scale, uint16_t fcolor)
{
	char buffer[16];
	uint8_t z;
	for (z=0;z<16;z++) buffer[z]=0;
	dtostrf(zahl,sges,snach,buffer);
	S6e63d6_print_string(x, y, (unsigned char *) buffer, scale, fcolor, BLACK);
}

void S6e63d6_putf_2(uint16_t x, uint16_t y, float zahl, int sges, int snach, uint8_t scale, uint16_t fcolor)
{
	char buffer[16];
	uint8_t z, xscale=scale, pre=sges+snach;

	if (scale > 1) xscale--;

	for (z=0;z<16;z++) buffer[z]=0;
	dtostrf(zahl,sges,snach,buffer);

	// Wenn sges nicht komplett gefüllt, dann vorne spaces rein

	z = strlen(buffer);
	if ( z <= pre )
	{
		pre = pre - z;
		for (z=0; z < pre ; z++)
		{
			S6e63d6_print_char(x, y, ' ', scale, fcolor, BLACK); // display a space at point (x,y)
			x = x + 8 * xscale;
		}
	}	
	z=0;
	while(buffer[z])
	{
		if (buffer[z] == '.') { z++; scale--; y = y + 12; };
		if(x <= 320)
		{
			S6e63d6_print_char(x, y, buffer[z++], scale, fcolor, BLACK); // display a character at point (x,y)
			x = x + 8 * xscale;
		}
	}
}
