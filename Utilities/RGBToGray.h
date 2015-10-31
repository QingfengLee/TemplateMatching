/*
 * RGBToGray.h
 *
 *  Created on: 31-Oct-2015
 *      Author: indudinesh
 */

#ifndef UTILITIES_RGBTOGRAY_H_
#define UTILITIES_RGBTOGRAY_H_

#include "misc.h"
#include "matrix.h"

struct matrix* convertRGBToGrayScale(uint8* rgb,uint32 rgbSize,uint32 width,uint32 height);

#endif /* UTILITIES_RGBTOGRAY_H_ */
