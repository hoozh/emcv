////////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                 License For Embedded Computer Vision Library
//
// Copyright (C) 2008, Shenzhen Institute of Advanced Technology, Chinese Academy of Sciences.
// Copyright (C) 2000, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of Intel Corporation may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//
#include "cxcore.h"
#include <stdio.h>

typedef struct
{
	char type1;
	char type2;
}BmpFileHead;
typedef struct
{
    unsigned int imageSize;
    unsigned int blank;
    unsigned int startPosition;
    unsigned int    length;
    unsigned int    width;
    unsigned int    height;
    unsigned short    colorPlane;
    unsigned short    bitColor;
    unsigned int    zipFormat;
    unsigned int    realSize;
    unsigned int    xPels;
    unsigned int    yPels;
    unsigned int    colorUse;
    unsigned int    colorImportant;
}BmpInfoHead;


typedef struct{
	unsigned char G;
	unsigned char B;
	unsigned char R;
	unsigned char A;
}RGBA;

CV_IMPL IplImage*
cvLoadImage( const char* filename, int flags)
{
	int channels;
	FILE * p;
	BmpFileHead bmpfilehead;
	BmpInfoHead bmpinfohead;
	int step, modbytes, idx;
    IplImage* image = 0;

    CV_FUNCNAME( "cvLoadImage" );

    __BEGIN__;

    if( !filename || strlen(filename) == 0 )
        CV_ERROR( CV_StsNullPtr, "null filename" );

 	p = fopen(filename, "r");
 	if(!p)
 		CV_ERROR( CV_StsNullPtr, "Can not open file" );
	
	fread(&bmpfilehead, sizeof(BmpFileHead), 1, p);
	fread(&bmpinfohead, sizeof(BmpInfoHead), 1, p);
	
	if( (bmpfilehead.type1 != 'B' && bmpfilehead.type1 != 'b') ||
		(bmpfilehead.type2 != 'M' && bmpfilehead.type2 != 'm') )
		CV_ERROR( CV_StsUnsupportedFormat, "The file is not a BMP file" );
		
	channels = bmpinfohead.bitColor / 8;
	if( channels != 1 && channels != 3)
		CV_ERROR( CV_StsUnsupportedFormat, "Only 1 or 3 channels images can be loaded." );
	
	if(bmpinfohead.width <= 0 || bmpinfohead.height <=0)
		CV_ERROR( CV_StsOutOfRange, "Bad image size");

 	modbytes = (bmpinfohead.width*channels)%4;
 	step = modbytes ? ((bmpinfohead.width*channels)-modbytes+4)  : (bmpinfohead.width*channels);

	image = cvCreateImage(cvSize(bmpinfohead.width, bmpinfohead.height), 8, channels);
	fseek(p, bmpinfohead.startPosition, SEEK_SET);
	for(idx=bmpinfohead.height-1; idx >= 0 ; idx--)
		fread(image->imageData+image->widthStep*idx, step, 1, p);

	fclose(p);
	__END__;
	return image;
}


CV_IMPL int
cvSaveImage( const char* filename, const IplImage * image )
{
	int channels;
	FILE * p;
	BmpFileHead bmpfilehead;
	BmpInfoHead bmpinfohead;
	RGBA rgba;
	int step, modbytes, idx;

	CV_FUNCNAME( "cvSaveImage" );
    __BEGIN__;

    channels = image->nChannels;
    if( channels != 3 && channels != 1)
        CV_ERROR( CV_BadNumChannels, "Only 1 or 3-channel image is supported" );

    if( !filename || strlen(filename) == 0 )
        CV_ERROR( CV_StsNullPtr, "null filename" );

 	p = fopen(filename, "wb");
 	if(!p)
 		CV_ERROR( CV_StsNullPtr, "Can not create file" );
 	
 	modbytes = (image->width*channels)%4;
 	step = modbytes ? ((image->width*channels)-modbytes+4)  : (image->width*channels);
 	
 	//bmpfilehead = (BmpFileHead *)cvAlloc(sizeof(BmpFileHead));
 	//bmpinfohead = (BmpInfoHead *)cvAlloc(sizeof(BmpInfoHead));
 	
 	memset(&bmpfilehead, 0, sizeof(BmpFileHead));
 	memset(&bmpinfohead, 0, sizeof(BmpInfoHead));
 	memset(&rgba, 0, sizeof(RGBA));
 	
 	bmpfilehead.type1='B';
 	bmpfilehead.type2='M';
 	
 	bmpinfohead.imageSize = ( 2+sizeof(BmpInfoHead)+image->height*step );
 	bmpinfohead.startPosition = (channels==3) ? (2+sizeof(BmpInfoHead)) : (2+sizeof(BmpInfoHead)+1024);
 	bmpinfohead.length = 40;
 	bmpinfohead.width = (image->width);
 	bmpinfohead.height = (image->height);
 	bmpinfohead.colorPlane = (1);
 	bmpinfohead.bitColor = (channels==3) ?(24) : 8;
 	bmpinfohead.realSize = (image->height*step);

	//write header
	fwrite(&bmpfilehead, sizeof(BmpFileHead), 1, p);
	fwrite(&bmpinfohead, sizeof(BmpInfoHead), 1, p);

	//write 
	if(channels==1)
	{
		for(idx =0; idx<256; idx++)
		{
			rgba.R=idx;
			rgba.G=idx;
			rgba.B=idx;
			rgba.A = 0;
			fwrite(&rgba, sizeof(RGBA), 1, p);
		}
	}
	
	for(idx = image->height-1; idx >=0 ; idx--)
 		fwrite(image->imageData+image->widthStep*idx, step, 1, p);
 	
 	fclose(p);
    __END__;
    
    return 0;
}
