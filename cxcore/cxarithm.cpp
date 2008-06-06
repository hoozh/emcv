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

/* ////////////////////////////////////////////////////////////////////
//
//  CvMat arithmetic operations: +, - ...
//
// */

#include "_cxcore.h"

/****************************************************************************************\
*                       External Functions for Arithmetic Operations                     *
\****************************************************************************************/

/*************************************** S U B ******************************************/

/*
CV_IMPL void
cvSub( const void* srcarr1, const void* srcarr2,
       void* dstarr, const void* maskarr )
{
    uchar* buffer = 0;

    CV_FUNCNAME( "cvSub" );

    __BEGIN__;

    const CvArr* tmp;
    int y, dy, type, depth, cn, cont_flag = 0;
    int src1_step, src2_step, dst_step, tdst_step, mask_step;
    CvMat srcstub1, srcstub2, *src1, *src2;
    CvMat dststub,  *dst = (CvMat*)dstarr;
    CvMat maskstub, *mask = (CvMat*)maskarr;
    CvMat dstbuf, *tdst;
    CvFunc2D_3A func;
    CvFunc2D_3A1I func_sfs;
    CvCopyMaskFunc copym_func;
    CvSize size, tsize;

    CV_SWAP( srcarr1, srcarr2, tmp ); // to comply with IPP
    src1 = (CvMat*)srcarr1;
    src2 = (CvMat*)srcarr2;

    if( !CV_IS_MAT(src1) || !CV_IS_MAT(src2) || !CV_IS_MAT(dst))
        CV_ERROR_FROM_CODE( CV_StsUnmatchedFormats );

    if( !CV_ARE_TYPES_EQ( src1, src2 ) || !CV_ARE_TYPES_EQ( src1, dst ))
        CV_ERROR_FROM_CODE( CV_StsUnmatchedFormats );

    if( !CV_ARE_SIZES_EQ( src1, src2 ) || !CV_ARE_SIZES_EQ( src1, dst ))
        CV_ERROR_FROM_CODE( CV_StsUnmatchedSizes );

	if( !mask )
		CV_ERROR(CV_StsUnsupportedFormat, "mask is not supported now");
	
    type = CV_MAT_TYPE(src1->type);
    size = cvGetMatSize( src1 );
    depth = CV_MAT_DEPTH(type);
    cn = CV_MAT_CN(type);

    __END__;

    cvFree( &buffer );
}
*/


/* End of file. */
