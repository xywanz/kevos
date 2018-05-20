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


inline int isalpha(int ch)   //Check whether ch is a letter.
{
    return _ctype[ch]&(_UPPER|_LOWER);
}

inline int isdigit(int ch)   //Check whether ch is a digit.
{
    return _ctype[ch]&_DIGIT;
}

inline int isxdigit(int ch)
{
    return _ctype[ch]&_HEX;
}

inline int isalnum(int ch)
{
    return _ctype[ch]&(_DIGIT|_ALPHA);
}

inline int iscntrl(int ch)   //Check whether ch is a Control Character. That is to say, 0<=ch<=0x1F.
{
    return _ctype[ch]&_CONTROL;
}

inline int isgraph(int ch)   //Check whether ch is a displayable character. (0x21<=ch<=0x7E).
{
    return _ctype[ch]&(_PUNCT|_UPPER|_LOWER|_DIGIT);
}

inline int islower(int ch)   //Check whether ch is a lowercase.
{
    return _ctype[ch]&_LOWER;
}

inline int isupper(int ch)
{
    return _ctype[ch]&_UPPER;
}

inline int isprint(int ch)
{
    return _ctype[ch]&(_BLANK|_PUNCT|_UPPER|_LOWER|_DIGIT);
}

inline int ispunct(int ch)
{
    return _ctype[ch]&_PUNCT;
}

inline int isspace(int ch)
{
    return _ctype[ch]&_SPACE;
}

inline int isascii(int ch)
{
    return ((unsigned char)ch)<0x80;
}

inline int tolower(int ch)
{
    return ch+0x20;
}

inline int toupper(int ch)
{
    return ch-0x20;
}


#endif