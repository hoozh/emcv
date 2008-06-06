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

#include "cv.h"

#define CV_8U   0
#define CV_8S   1
#define CV_16U  2
#define CV_16S  3
#define CV_32S  4
#define CV_32F  5
#define CV_64F  6
#define CV_USRTYPE1 7



CV_IMPL void
cvPyrUp( const void* srcarr, void* dstarr, int filter )
{

    CV_FUNCNAME( "cvPyrUp" );

    __BEGIN__;

    int coi1 = 0, coi2 = 0;
    int type, depth, cn;
    CvMat srcstub, *src = (CvMat*)srcarr;
    CvMat dststub, *dst = (CvMat*)dstarr;
    int c, r;
	register size_t pixel_size;

    CV_CALL( src = cvGetMat( src, &srcstub, &coi1 ));
    CV_CALL( dst = cvGetMat( dst, &dststub, &coi2 ));

    if( coi1 != 0 || coi2 != 0 )
        CV_ERROR( CV_BadCOI, "" );

    if( filter != 0 )
        CV_ERROR( CV_StsBadArg, "filters are not supported now" );

    if( !CV_ARE_TYPES_EQ( src, dst ))
        CV_ERROR( CV_StsUnmatchedFormats, "" );

    if( src->cols*2 != dst->cols || src->rows*2 != dst->rows )
        CV_ERROR( CV_StsUnmatchedSizes, "" );

    type = CV_MAT_TYPE(src->type);
    depth = CV_MAT_DEPTH(type);
    cn = CV_MAT_CN(type);

    if( cn != 1 && cn != 3 )
        CV_ERROR( CV_StsUnsupportedFormat, "The images must have 1 or 3 channel" );

	pixel_size = CV_DEPTH_BYTES[depth]*cn;
	for(r = 0; r < src->rows; r++)	
	{
		for(c = 0; c < src->cols; c++)
		{
			unsigned char * psrc = src->data.ptr + r*src->step + c*pixel_size;
			unsigned char * pdst = dst->data.ptr + 2*r*dst->step + 2*c*pixel_size;
			memcpy(pdst, psrc, pixel_size);
			pdst += pixel_size;
			memcpy(pdst, psrc, pixel_size);
			pdst = dst->data.ptr + (2*r+1)*dst->step + 2*c*pixel_size;
			memcpy(pdst, psrc, pixel_size);
			pdst += pixel_size;
			memcpy(pdst, psrc, pixel_size);
		}
	}

    __END__;

}



CV_IMPL void
cvPyrDown( const void* srcarr, void* dstarr, int filter )
{

    CV_FUNCNAME( "cvPyrDown" );

    __BEGIN__;

    int coi1 = 0, coi2 = 0;
    int type,depth, cn;
    CvMat srcstub, *src = (CvMat*)srcarr;
    CvMat dststub, *dst = (CvMat*)dstarr;
    int c, r;
	register size_t pixel_size;

    CV_CALL( src = cvGetMat( src, &srcstub, &coi1 ));
    CV_CALL( dst = cvGetMat( dst, &dststub, &coi2 ));

    if( coi1 != 0 || coi2 != 0 )
        CV_ERROR( CV_BadCOI, "" );

    if( filter != 0 )
        CV_ERROR( CV_StsBadArg, "filters are not supported now" );

    if( !CV_ARE_TYPES_EQ( src, dst ))
        CV_ERROR( CV_StsUnmatchedFormats, "" );

    if( src->cols != dst->cols*2 || src->rows != dst->rows*2 )
        CV_ERROR( CV_StsUnmatchedSizes, "" );

    type = CV_MAT_TYPE(src->type);
    depth = CV_MAT_DEPTH(type);
    cn = CV_MAT_CN(type);

    if( cn != 1 && cn != 3 )
        CV_ERROR( CV_StsUnsupportedFormat, "The images must have 1 or 3 channel" );

	pixel_size = CV_DEPTH_BYTES[depth]*cn;
	for(r = 0; r < dst->rows; r++)	
	{
		for(c = 0; c < dst->cols; c++)
		{
			unsigned char * psrc = src->data.ptr + 2*r*src->step + 2*c*pixel_size;
			unsigned char * pdst = dst->data.ptr + r*dst->step + c*pixel_size;
			memcpy(pdst, psrc, pixel_size);
		}
	}

    __END__;

}

