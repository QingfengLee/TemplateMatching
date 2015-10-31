/*
 * imfilter.c
 *
 *  Created on: 31-Oct-2015
 *      Author: Indumathi Duraipandian
 */

#include "imfilter.h"

void imfilter(struct matrix* image,struct matrix* filter,struct matrix* filteredImage,uint8 operation,uint8 mode){

	float tempResult ;
	float tempPixelValue = 0.0;
#ifdef DEBUG
	struct matrix tempMatrix;
	initMatrix(&tempMatrix,filter->numberOfRows,filter->numberOfColumns);
#endif
	for (uint16 i = 0; i < image->numberOfRows; ++i) {
		for (uint16 j = 0; j < image->numberOfColumns; ++j) {
				tempResult = 0.0;
				for (int l = 0; l < filter->numberOfRows; ++l) {
					for (int m = 0; m < filter->numberOfColumns; ++m) {
						tempPixelValue = getPixelValue(image,i,j,l-(filter->numberOfRows/2),m-(filter->numberOfColumns/2),mode);
#ifdef DEBUG
						MAT(&tempMatrix,l,m) = tempPixelValue;
#endif
						if(operation == CONVOLUTION_OPERATION)
						{
							tempResult = tempResult + (tempPixelValue * MAT(filter,(filter->numberOfRows-1-l),(filter->numberOfColumns-1-m)));
						}
						else
						{
							tempResult = tempResult + (tempPixelValue * MAT(filter,l,m));
						}
					}
				}
#ifdef DEBUG
				printMatrix(&tempMatrix);
#endif
				MAT(filteredImage,i,j) = tempResult;

		}
	}

	printMatrix(filteredImage);
}



float getPixelValue(struct matrix* image,uint32 imgPosX,uint32 imgPosY,
		uint32 filterPosX,uint32 filterPosY,uint8 mode)
{
	float pixelValue = 0.0;

	sint32 imgCurrentPosX = imgPosX+filterPosX;
	sint32 imgCurrentPosY = imgPosY+filterPosY;
	if((imgCurrentPosX < 0) ||
		(imgCurrentPosX > (image->numberOfRows-1)) ||
		(imgCurrentPosY < 0) ||
		(imgCurrentPosY > (image->numberOfColumns-1)))
	{
			if(mode == MODE_REPLICATE)
			{
				imgCurrentPosX = ((imgCurrentPosX < 0) ? 0 : (imgCurrentPosX > image-> numberOfRows-1) ? (image-> numberOfRows-1) : imgCurrentPosX);
				imgCurrentPosY = ((imgCurrentPosY < 0) ? 0 : (imgCurrentPosY > image-> numberOfColumns-1) ? (image-> numberOfColumns-1) : imgCurrentPosY);

				pixelValue = MAT(image,imgCurrentPosX,imgCurrentPosY);
			}
			else if(mode == MODE_SYMMETRIC)
			{
				if(imgCurrentPosX < 0 || imgCurrentPosX > image->numberOfRows-1)
				{
					imgCurrentPosX = (image->numberOfRows -1) - (mod(imgCurrentPosX,image->numberOfRows));
				}
				if(imgCurrentPosY < 0 || imgCurrentPosY > image->numberOfColumns-1)
				{
					imgCurrentPosY = (image->numberOfColumns -1) - (mod(imgCurrentPosY,image->numberOfColumns));
				}

				pixelValue = MAT(image,imgCurrentPosX,imgCurrentPosY);
			}
			else if(mode == MODE_CIRCULAR)
			{
				if(imgCurrentPosX < 0 || imgCurrentPosX > image->numberOfRows-1)
				{
					imgCurrentPosX = mod(imgCurrentPosX,image->numberOfRows);
				}
				if(imgCurrentPosY < 0 || imgCurrentPosY > image->numberOfColumns-1)
				{
					imgCurrentPosY = mod(imgCurrentPosY,image->numberOfColumns);
				}

				pixelValue = MAT(image,imgCurrentPosX,imgCurrentPosY);
			}
	}
	else
	{
		pixelValue = MAT(image,imgCurrentPosX,imgCurrentPosY);
	}

	return pixelValue;

}


