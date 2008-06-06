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

CV_IMPL  void
cvAbsDiff( const void* srcarr1, const void* srcarr2, void* dstarr )
{

    CV_FUNCNAME( "cvAbsDiff" );

    __BEGIN__;

    int coi1 = 0, coi2 = 0, coi3 = 0;
    CvMat srcstub1, *src1 = (CvMat*)srcarr1;
    CvMat srcstub2, *src2 = (CvMat*)srcarr2;
    CvMat dststub,  *dst = (CvMat*)dstarr;
    CvSize size;
    int type, depth, pixel_size;

    CV_CALL( src1 = cvGetMat( src1, &srcstub1, &coi1 ));
    CV_CALL( src2 = cvGetMat( src2, &srcstub2, &coi2 ));
    CV_CALL( dst = cvGetMat( dst, &dststub, &coi3 ));

    if( coi1 != 0 || coi2 != 0 || coi3 != 0 )
        CV_ERROR( CV_BadCOI, "" );

    if( !CV_ARE_SIZES_EQ( src1, src2 ) )
        CV_ERROR_FROM_CODE( CV_StsUnmatchedSizes );

    type = CV_MAT_TYPE(src1->type);
    depth = CV_MAT_DEPTH(type);

    if( !CV_ARE_SIZES_EQ( src1, dst ))
        CV_ERROR_FROM_CODE( CV_StsUnmatchedSizes );

    if( !CV_ARE_TYPES_EQ( src1, src2 ))
        CV_ERROR_FROM_CODE( CV_StsUnmatchedFormats );

    if( !CV_ARE_TYPES_EQ( src1, dst ))
        CV_ERROR_FROM_CODE( CV_StsUnmatchedFormats );

    size.width = src1->step * src1->height;
    size.height = 1;
	pixel_size = CV_DEPTH_BYTES[depth];

	if(depth == CV_8U)
	{
		int idx;
		unsigned char * p1;
		unsigned char * p2;
		unsigned char * pdst; 
		p1 = src1->data.ptr ; 
		p2 = src2->data.ptr; 
		pdst = dst->data.ptr; 
       	for (idx = 0; idx < size.width/pixel_size; idx+=4)
       	{
       		_amem4(pdst) = _subabs4(_amem4_const(p1), _amem4_const(p2) );
       		p1 += 4;
       		p2 += 4;
       		pdst += 4;
       	}	
    }
	else if(depth == CV_32S)        
	{
		int idx;
		int * p1;
		int * p2;
		int * pdst; 
		p1 = src1->data.i; 
		p2 = src2->data.i; 
		pdst = dst->data.i;
       	for (idx = 0; idx < size.width/pixel_size; idx++)
       	{
       		*pdst = _abs(_ssub(*p1, *p2));
       		p1 += 1;
       		p2 += 1;
       		pdst += 1;
       	}	
    }
    else
    {
		CV_ERROR( CV_StsUnsupportedFormat, "unsupported matrix type." );
	}

    __END__;
}

