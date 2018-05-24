/* Copyright 2018 kevin Lau (http://github.com/stormycatcat)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CTYPES_H_
#define _CTYPES_H_


#define _UPPER          0x1     /* upper case letter */
#define _LOWER          0x2     /* lower case letter */
#define _DIGIT          0x4     /* digit[0-9] */
#define _SPACE          0x8     /* tab, carriage return, newline, */
                                /* vertical tab or form feed */
#define _PUNCT          0x10    /* punctuation character */
#define _CONTROL        0x20    /* control character */
#define _BLANK          0x40    /* space char */
#define _HEX            0x80    /* hexadecimal digit */

#define _LEADBYTE       0x8000                  /* multibyte leadbyte */
#define _ALPHA          (0x0100|_UPPER|_LOWER)  /* alphabetic character */


extern unsigned short _ctype[];


int isalpha(int ch);

int isdigit(int ch);

int isxdigit(int ch);

int isalnum(int ch);

int iscntrl(int ch);

int isgraph(int ch);

int islower(int ch);

int isupper(int ch);

int isprint(int ch);

int ispunct(int ch);

int isspace(int ch);

int isascii(int ch);

int tolower(int ch);

int toupper(int ch);


#endif

#ifdef __cplusplus
}
#endif