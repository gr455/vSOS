#ifndef UTYPES_H
#define UTYPES_H

typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;
typedef          char  sint8_t;
typedef unsigned char bool;

// bools
#define true  1
#define false 0

#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)
#define NULL 0
#endif