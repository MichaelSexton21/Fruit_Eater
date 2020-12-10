/*
 * packman.h
 *
 *  Created on: Nov 25, 2020
 *  Authors: Michael Sexton and Jack Bybel
 *
 */
#ifndef __PACKMAN_H__
#define __PACKMAN_H__

#include <stdint.h>

// packman bitmap sizes
extern const uint8_t packman_WidthPixels;
extern const uint8_t packman_HeightPixels;

// fruit bitmap sizes
extern const uint8_t fruitWidthPixels;
extern const uint8_t fruitHeightPixels;

// blank screen bitmap sizes
extern const uint8_t blankWidthPixels;
extern const uint8_t blankHeightPixels;

// packman bitmaps
extern uint8_t packman_rightBitmaps[];
extern uint8_t packman_leftBitmaps[];
extern uint8_t packman_upBitmaps[];
extern uint8_t packman_downBitmaps[];

// fruit bitmaps
extern uint8_t orangeBitmaps[];
extern uint8_t bannanaBitmaps[];
extern uint8_t appleBitmaps[];
extern const uint8_t blankScreenBitmaps[];


#endif
