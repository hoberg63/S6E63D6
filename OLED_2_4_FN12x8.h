//!
//! @file OLED_2_4_FN12x8.h,v
//!
//! Copyright (c) 2011 HB-Best Weinheim
//!
//! @version 1.0 $Id: MS5541.c,v 1.0
//!
//! @todo

//_____ I N C L U D E S

#include <avr/pgmspace.h>
#define MAXCHARS 75

char fchar[] PROGMEM = {
0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // Leerzeichen
0x00,0x30,0x78,0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0x00,0x00,	// A
0x00,0xFC,0x66,0x66,0x66,0x7C,0x66,0x66,0x66,0xFC,0x00,0x00,	// B
0x00,0x3C,0x66,0xC6,0xC0,0xC0,0xC0,0xC6,0x66,0x3C,0x00,0x00,	// C
0x00,0xF8,0x6C,0x66,0x66,0x66,0x66,0x66,0x6C,0xF8,0x00,0x00,	// D
0x00,0xFE,0x62,0x60,0x64,0x7C,0x64,0x60,0x62,0xFE,0x00,0x00,	// E
0x00,0xFE,0x66,0x62,0x64,0x7C,0x64,0x60,0x60,0xF0,0x00,0x00,	// F
0x00,0x3C,0x66,0xC6,0xC0,0xC0,0xCE,0xC6,0x66,0x3E,0x00,0x00,	// G
0x00,0xCC,0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0xCC,0x00,0x00,	// H
0x00,0x78,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x78,0x00,0x00,	// I
0x00,0x1E,0x0C,0x0C,0x0C,0x0C,0xCC,0xCC,0xCC,0x78,0x00,0x00,	// J
0x00,0xE6,0x66,0x6C,0x6C,0x78,0x6C,0x6C,0x66,0xE6,0x00,0x00,	// K
0x00,0xF0,0x60,0x60,0x60,0x60,0x62,0x66,0x66,0xFE,0x00,0x00,	// L
0x00,0xC6,0xEE,0xFE,0xFE,0xD6,0xC6,0xC6,0xC6,0xC6,0x00,0x00,	// M
0x00,0xC6,0xC6,0xE6,0xF6,0xFE,0xDE,0xCE,0xC6,0xC6,0x00,0x00,	// N
0x00,0x38,0x6C,0xC6,0xC6,0xC6,0xC6,0xC6,0x6C,0x38,0x00,0x00,	// O
0x00,0xFC,0x66,0x66,0x66,0x7C,0x60,0x60,0x60,0xF0,0x00,0x00,	// P
0x00,0x38,0x6C,0xC6,0xC6,0xC6,0xCE,0xDE,0x7C,0x0C,0x1E,0x00,	// Q
0x00,0xFC,0x66,0x66,0x66,0x7C,0x6C,0x66,0x66,0xE6,0x00,0x00,	// R
0x00,0x78,0xCC,0xCC,0xC0,0x70,0x18,0xCC,0xCC,0x78,0x00,0x00,	// S
0x00,0xFC,0xB4,0x30,0x30,0x30,0x30,0x30,0x30,0x78,0x00,0x00,	// T
0x00,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0x78,0x00,0x00,	// U
0x00,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0x78,0x30,0x00,0x00,	// V
0x00,0xC6,0xC6,0xC6,0xC6,0xD6,0xD6,0x6C,0x6C,0x6C,0x00,0x00,	// W
0x00,0xCC,0xCC,0xCC,0x78,0x30,0x78,0xCC,0xCC,0xCC,0x00,0x00,	// X
0x00,0xCC,0xCC,0xCC,0xCC,0x78,0x30,0x30,0x30,0x78,0x00,0x00,	// Y
0x00,0xFE,0xCE,0x98,0x18,0x30,0x60,0x62,0xC6,0xFE,0x00,0x00,	// Z
0x00,0x00,0x00,0x00,0x78,0x0C,0x7C,0xCC,0xCC,0x76,0x00,0x00,	// a
0x00,0xE0,0x60,0x60,0x7C,0x66,0x66,0x66,0x66,0xDC,0x00,0x00,	// b
0x00,0x00,0x00,0x00,0x78,0xCC,0xC0,0xC0,0xCC,0x78,0x00,0x00,	// c
0x00,0x1C,0x0C,0x0C,0x7C,0xCC,0xCC,0xCC,0xCC,0x76,0x00,0x00,	// d
0x00,0x00,0x00,0x00,0x78,0xCC,0xFC,0xC0,0xCC,0x78,0x00,0x00,	// e
0x00,0x38,0x6C,0x60,0x60,0xF8,0x60,0x60,0x60,0xF0,0x00,0x00,	// f
0x00,0x00,0x00,0x00,0x76,0xCC,0xCC,0xCC,0x7C,0x0C,0xCC,0x78,	// g
0x00,0xE0,0x60,0x60,0x6C,0x76,0x66,0x66,0x66,0xE6,0x00,0x00,	// h
0x00,0x18,0x18,0x00,0x78,0x18,0x18,0x18,0x18,0x7E,0x00,0x00,	// i
0x00,0x0C,0x0C,0x00,0x3C,0x0C,0x0C,0x0C,0x0C,0xCC,0xCC,0x78,	// j
0x00,0xE0,0x60,0x60,0x66,0x6C,0x78,0x6C,0x66,0xE6,0x00,0x00,	// k
0x00,0x78,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x7E,0x00,0x00,	// l
0x00,0x00,0x00,0x00,0xFC,0xD6,0xD6,0xD6,0xD6,0xC6,0x00,0x00,	// m
0x00,0x00,0x00,0x00,0xF8,0xCC,0xCC,0xCC,0xCC,0xCC,0x00,0x00,	// n
0x00,0x00,0x00,0x00,0x78,0xCC,0xCC,0xCC,0xCC,0x78,0x00,0x00,	// o
0x00,0x00,0x00,0x00,0xDC,0x66,0x66,0x66,0x66,0x7C,0x60,0xF0,	// p
0x00,0x00,0x00,0x00,0x76,0xCC,0xCC,0xCC,0xCC,0x7C,0x0C,0x1E,	// q
0x00,0x00,0x00,0x00,0xEC,0x6E,0x76,0x60,0x60,0xF0,0x00,0x00,	// r
0x00,0x00,0x00,0x00,0x78,0xCC,0x60,0x18,0xCC,0x78,0x00,0x00,	// s
0x00,0x00,0x20,0x60,0xFC,0x60,0x60,0x60,0x6C,0x38,0x00,0x00,	// t
0x00,0x00,0x00,0x00,0xCC,0xCC,0xCC,0xCC,0xCC,0x76,0x00,0x00,	// u
0x00,0x00,0x00,0x00,0xCC,0xCC,0xCC,0xCC,0x78,0x30,0x00,0x00,	// v
0x00,0x00,0x00,0x00,0xC6,0xC6,0xD6,0xD6,0x6C,0x6C,0x00,0x00,	// w
0x00,0x00,0x00,0x00,0xC6,0x6C,0x38,0x38,0x6C,0xC6,0x00,0x00,	// x
0x00,0x00,0x00,0x00,0x66,0x66,0x66,0x66,0x3C,0x0C,0x18,0xF0,	// y
0x00,0x00,0x00,0x00,0xFC,0x8C,0x18,0x60,0xC4,0xFC,0x00,0x00,	// z
0x00,0x7C,0xC6,0xCE,0xDE,0xD6,0xF6,0xE6,0xC6,0x7C,0x00,0x00,	// 0
0x00,0x10,0x30,0xF0,0x30,0x30,0x30,0x30,0x30,0xFC,0x00,0x00,	// 1
0x00,0x78,0xCC,0xCC,0x0C,0x18,0x30,0x60,0xCC,0xFC,0x00,0x00,	// 2
0x00,0x78,0xCC,0x0C,0x0C,0x38,0x0C,0x0C,0xCC,0x78,0x00,0x00,	// 3
0x00,0x0C,0x1C,0x3C,0x6C,0xCC,0xFE,0x0C,0x0C,0x1E,0x00,0x00,	// 4
0x00,0xFC,0xC0,0xC0,0xC0,0xF8,0x0C,0x0C,0xCC,0x78,0x00,0x00,	// 5
0x00,0x38,0x60,0xC0,0xC0,0xF8,0xCC,0xCC,0xCC,0x78,0x00,0x00,	// 6
0x00,0xFE,0xC6,0xC6,0x06,0x0C,0x18,0x30,0x30,0x30,0x00,0x00,	// 7
0x00,0x78,0xCC,0xCC,0xCC,0x78,0xCC,0xCC,0xCC,0x78,0x00,0x00,	// 8
0x00,0x78,0xCC,0xCC,0xCC,0x7C,0x18,0x18,0x30,0x70,0x00,0x00,	// 9
0x00,0x00,0x00,0x38,0x38,0x00,0x00,0x38,0x38,0x00,0x00,0x00,	// :
0x00,0x30,0x78,0x78,0x78,0x30,0x30,0x00,0x30,0x30,0x00,0x00,	// ! Chr(33)
0x00,0x00,0x00,0xC4,0xCC,0x18,0x30,0x60,0xCC,0x8C,0x00,0x00,	// % Chr(37)
0x00,0x00,0x00,0x18,0x18,0x7E,0x18,0x18,0x00,0x00,0x00,0x00,	// + Chr(43)
0x00,0x00,0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,	// - Chr(45)
0x00,0x78,0xCC,0x0C,0x18,0x30,0x30,0x00,0x30,0x30,0x00,0x00,	// ? (Chr(63)
0x00,0x78,0xCC,0xCC,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// � Grad Celsius Chr(167)
0x00,0x60,0x30,0x18,0x0C,0x06,0x0C,0x18,0x30,0x60,0x00,0x00,	// > Chr(62)
0x00,0x0C,0x18,0x30,0x60,0xC0,0x60,0x30,0x18,0x0C,0x00,0x00,	// < Chr(60)
0x00,0x00,0x02,0x06,0x0C,0x18,0x30,0x60,0xC0,0x80,0x00,0x00,	// / Chr(47)
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x38,0x00,0x00,	// . Chr(46)
0x00,0x18,0x18,0x3C,0x7E,0x99,0x18,0x3C,0x42,0x00,0x00,0x00		// Airplane
};

// Lookup-Tabelle fuer Zeichenposition
// ASCII-Wert => Arraypos
char arraypos[]={
32, // Leerzeichen
65, //A...
66,
67,
68,
69,
70,
71,
72,
73,
74,
75,
76,
77,
78,
79,
80,
81,
82,
83,
84,
85,
86,
87,
88,
89,
90,  //...Z
97,  //...a
98,
99,
100,
101,
102,
103,
104,
105,
106,
107,
108,
109,
110,
111,
112,
113,
114,
115,
116,
117,
118,
119,
120,
121,
122, //...z
48,  //0...
49,
50,
51,
52,
53,
54,
55,
56,
57, //...9
58, //:
33, //!
37, //%
43, //+
45, //-
63, //?
176, //�
62, // >
60, // <
47, // /
46,  // .
177 // Airplane
};
