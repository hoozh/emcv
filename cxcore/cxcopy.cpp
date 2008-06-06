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
//  CvMat basic operations: cvCopy, cvSet
//
// */

#include "_cxcore.h"

/////////////////////////////////////////////////////////////////////////////////////////
//                                                                                     //
//                                  L/L COPY & SET FUNCTIONS                           //
//                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////
/*
IPCVAPI_IMPL( CvStatus, icvCopy_8u_C1R, ( const uchar* src, int srcstep,
                                          uchar* dst, int dststep, CvSize size ),
                                          (src, srcstep, dst, dststep, size) )
{
    for( ; size.height--; src += srcstep, dst += dststep )
        memcpy( dst, src, size.width );

    return  CV_OK;
}
*/
CV_IMPL CvStatus icvCopy_8u_C1R( const uchar* src, int srcstep, uchar* dst, int dststep, CvSize size )
{
    for( ; size.height--; src += srcstep, dst += dststep )
        memcpy( dst, src, size.width );

    return  CV_OK;
}

/* dst = src */
CV_IMPL void
cvCopy( const void* srcarr, void* dstarr, const void* maskarr )
{
    CV_FUNCNAME( "cvCopy" );
    
    __BEGIN__;

    int pix_size;
    CvMat *src = (CvMat*)srcarr;
    CvMat *dst = (CvMat*)dstarr;
    CvSize size;

    if( !CV_IS_MAT(src) || !CV_IS_MAT(dst) )
        CV_ERROR_FROM_CODE( CV_StsUnmatchedFormats );

    if( !CV_ARE_TYPES_EQ( src, dst ))
        CV_ERROR_FROM_CODE( CV_StsUnmatchedFormats );

    if( !CV_ARE_SIZES_EQ( src, dst ))
        CV_ERROR_FROM_CODE( CV_StsUnmatchedSizes );

    size = cvGetMatSize( src );
    pix_size = CV_ELEM_SIZE(src->type);

    if( !maskarr )
    {
        int src_step = src->step, dst_step = dst->step;
        size.width *= pix_size;
        if( CV_IS_MAT_CONT( src->type & dst->type ) && (src_step == dst_step) && (src_step == src->width * pix_size))
        {
            size.width *= size.height;

            if( size.width <= CV_MAX_INLINE_MAT_OP_SIZE*
                              CV_MAX_INLINE_MAT_OP_SIZE*(int)sizeof(double))
            {
                memcpy( dst->data.ptr, src->data.ptr, size.width );
                EXIT;
            }

            size.height = 1;
            src_step = dst_step = CV_STUB_STEP;
        }

        icvCopy_8u_C1R( src->data.ptr, src_step,
                        dst->data.ptr, dst_step, size );
    }
    else
    {
        CV_ERROR( CV_StsUnsupportedFormat, "Mask is not supported currently" );
    }

    __END__;
}

/****************************************************************************************\
*                                          Clearing                                      *
\****************************************************************************************/

CV_IMPL void
cvSetZero( CvArr* arr )
{
    CV_FUNCNAME( "cvSetZero" );
    
    __BEGIN__;
    
    CvMat mat, *pmat;
    int coi = 0;
    
    CV_CALL( pmat = cvGetMat( arr, &mat, &coi ));
    
    memset(pmat->data.ptr, 0, pmat->step*pmat->height);

	__END__;
}
/* End of file. */

