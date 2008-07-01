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
// Copyright (c) 2008, EMCV Project,
// Copyright (c) 2000-2007, Intel Corporation,
// All rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification, 
// are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice, 
//      this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright notice, 
//      this list of conditions and the following disclaimer in the documentation 
//      and/or other materials provided with the distribution.
//    * Neither the name of the copyright holders nor the names of their contributors 
//      may be used to endorse or promote products derived from this software 
//      without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
// OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
// OF SUCH DAMAGE.
//
// Contributors:
//    * Shiqi Yu (Shenzhen Institute of Advanced Technology, Chinese Academy of Sciences)


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

