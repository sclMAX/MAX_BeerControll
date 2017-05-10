#ifndef IMAGENES_H
#define IMAGENES_H

#include <U8glib.h>
// Array generado con http://www.digole.com/tools/PicturetoC_Hex_converter.php
// Width:128, Height: 64
#define LOGO_WIDTH 16 // Nro de Columnas del Array
#define LOGO_HEIGHT 64 // Nro de Filas del Array
const unsigned char logo[] U8G_PROGMEM = {
  0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0xff,0xff
,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0xff,0xff
,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0xff,0xff
,0x20,0x00,0x00,0x00,0x00,0x01,0xe1,0xe7,0xc3,0xcf,0x00,0x00,0x00,0x07,0xff,0xff
,0x40,0x00,0x00,0x00,0x00,0x01,0xe1,0xe7,0xc3,0xcf,0x00,0x00,0x00,0x03,0xff,0xff
,0x40,0x00,0x00,0x00,0x00,0x00,0xe1,0xc1,0xc1,0x86,0x00,0x00,0x00,0x01,0xff,0xff
,0x80,0x00,0x00,0x00,0x00,0x00,0xf3,0xc3,0x60,0xcc,0x00,0x00,0x00,0x00,0xff,0xff
,0x80,0x1f,0x07,0x00,0x00,0x00,0xd2,0xc3,0x60,0x78,0x00,0x00,0x00,0x00,0x7f,0xff
,0x80,0x31,0xff,0x80,0x00,0x00,0xde,0xc6,0x30,0x30,0x00,0x00,0x00,0x00,0x3f,0xff
,0x80,0x60,0xf8,0xc0,0x00,0x00,0xcc,0xc7,0xf0,0x78,0x00,0x00,0x00,0x00,0x1f,0xff
,0x80,0x40,0x10,0xc0,0x00,0x00,0xcc,0xc7,0xf0,0xcc,0x00,0x00,0x00,0x00,0x0f,0xff
,0x80,0xc0,0x00,0xc0,0x00,0x00,0xc0,0xcc,0x19,0x86,0x00,0x00,0x00,0x00,0x07,0xff
,0x80,0xc0,0x01,0x80,0x00,0x01,0xf3,0xfe,0x3f,0xcf,0x00,0x00,0x00,0x00,0x03,0xff
,0x80,0x73,0xff,0x80,0x00,0x01,0xf3,0xfe,0x3f,0xcf,0x00,0x00,0x00,0x00,0x01,0xff
,0x80,0x73,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff
,0x80,0x73,0xff,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7f
,0x80,0x7f,0xff,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f
,0x80,0x7f,0xff,0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1f
,0x80,0x73,0x77,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x30,0x0f
,0x80,0x73,0x37,0x0c,0xfc,0x00,0x00,0x00,0x0f,0x00,0x00,0x18,0x00,0x03,0x30,0x07
,0x80,0x73,0x37,0x0c,0xfc,0x00,0x00,0x00,0x1f,0x80,0x00,0x18,0x00,0x03,0x30,0x03
,0x80,0x73,0x37,0x0c,0xee,0x00,0x00,0x00,0x1d,0x80,0x00,0x18,0x00,0x03,0x30,0x01
,0x80,0x73,0x33,0x0c,0xc6,0x38,0x30,0xc8,0x38,0x06,0x1b,0x3e,0x48,0xe3,0x30,0x01
,0x80,0x73,0x37,0x0c,0xc6,0x7c,0x7c,0xf8,0x30,0x0f,0x1f,0x3e,0xf9,0xf3,0x30,0x01
,0x80,0x73,0x37,0x0c,0xfc,0x6c,0x6c,0xf8,0x30,0x1b,0x9f,0x98,0xfb,0xb3,0x30,0x01
,0x80,0x73,0x37,0x0c,0xfc,0xc4,0xcc,0xe0,0x30,0x19,0x99,0x98,0xe3,0x1b,0x30,0x01
,0x80,0x7f,0xff,0x88,0xfe,0xee,0xee,0xe0,0x30,0x19,0x99,0x98,0xe3,0x1b,0x30,0x01
,0x80,0x7f,0xff,0xf8,0xc6,0xfe,0xfe,0xc0,0x30,0x30,0x99,0x98,0xc3,0x1b,0x30,0x01
,0x80,0x7f,0xff,0x80,0xc6,0xfc,0xfc,0xc0,0x30,0x31,0x99,0x98,0xc3,0x1b,0x30,0x01
,0x80,0x7f,0xff,0x00,0xc6,0xc0,0xc0,0xc0,0x38,0x99,0x99,0x98,0xc3,0x1b,0x30,0x01
,0x80,0x7f,0xff,0x00,0xfe,0x60,0x64,0xc0,0x1f,0x99,0x99,0x98,0xc3,0xb3,0x30,0x01
,0x80,0x7f,0xff,0x00,0xfe,0x7c,0x7c,0xc0,0x1f,0x8f,0x19,0x9e,0xc1,0xf3,0x30,0x01
,0x80,0x3f,0xff,0x00,0xfc,0x3c,0x38,0xc0,0x07,0x06,0x19,0x8e,0x40,0xe3,0x30,0x01
,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01
,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02
,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02
,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04
,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0c
,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18
,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60
,0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
#endif // IMAGENES_H