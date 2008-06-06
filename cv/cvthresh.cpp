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


#include "_cv.h"

CV_IMPL void
cvThreshold( const void* srcarr, void* dstarr, double thresh, double maxval, int type )
{
    CV_FUNCNAME( "cvThreshold" );

    __BEGIN__;

    CvMat src_stub, *src = (CvMat*)srcarr;
    CvMat dst_stub, *dst = (CvMat*)dstarr;
    int coi1 = 0, coi2 = 0;

    CV_CALL( src = cvGetMat( src, &src_stub, &coi1 ));
    CV_CALL( dst = cvGetMat( dst, &dst_stub, &coi2 ));

    if( coi1 + coi2 )
        CV_ERROR( CV_BadCOI, "COI is not supported by the function" );

    if( !CV_ARE_CNS_EQ( src, dst ) )
        CV_ERROR( CV_StsUnmatchedFormats, "Both arrays must have equal number of channels" );

	if( type != CV_THRESH_BINARY)
		CV_ERROR( CV_StsBadFlag, "Only binary threshold is supported now. Please use type=CV_THRESH_BINARY." );
	
    if( CV_MAT_TYPE(src->type) != CV_8UC1 || CV_MAT_TYPE(dst->type) != CV_8UC1)
        CV_ERROR( CV_StsUnsupportedFormat, "Types should be 8uC1" );

    switch( CV_MAT_DEPTH(src->type) )
    {
    case CV_8U:
        register unsigned char ithreshs[4];
        register unsigned char imaxvals[4];
        register unsigned int binvals;
	    int ithresh, imaxval;
	    int idx;
        
        ithresh = cvFloor(thresh);
        ithresh = (ithresh>255) ? 255 : ithresh;
        ithresh = (ithresh<0) ? 0 : ithresh;
        ithreshs[0]=ithreshs[1]=ithreshs[2]=ithreshs[3]=ithresh;
        
        imaxval = cvRound(maxval);
        imaxval = (imaxval>255) ? 255 : imaxval;
		imaxval = (imaxval<0) ? 0 : imaxval;
		imaxvals[0]=imaxvals[1]=imaxvals[2]=imaxvals[3]=imaxval;
		
		for(idx=0; idx < (src->step*src->height)/4; idx++)
		{
			binvals = _cmpgtu4( _mem4_const(src->data.i+idx), _mem4_const(ithreshs) );
			binvals = _xpnd4( binvals  );
			_mem4(dst->data.i+idx) = binvals & _mem4_const(imaxvals);
		}
        break;
    default:
        CV_ERROR( CV_BadDepth, cvUnsupportedFormat );
    }

    __END__;

}

/* End of file. */
