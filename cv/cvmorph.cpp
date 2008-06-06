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

void icvErode_8UC1
(
    const unsigned char *restrict in_data, 
    unsigned char       *restrict out_data, 
    const char          *restrict mask, 
    int cols,
    int step
)
{
    int i;
    unsigned m0, m1, m2, m3, m5, m6, m7, m8;
    unsigned p0, p1, p2, p3, p4, p5, p6, p7, p8;
    unsigned result;

    m0 = mask[0] < 0 ? 0 : 1;
    m1 = mask[1] < 0 ? 0 : 1;
    m2 = mask[2] < 0 ? 0 : 1;
    m3 = mask[3] < 0 ? 0 : 1;
    //m4 = mask[4] < 0 ? 0 : 1;
    m5 = mask[5] < 0 ? 0 : 1;
    m6 = mask[6] < 0 ? 0 : 1;
    m7 = mask[7] < 0 ? 0 : 1;
    m8 = mask[8] < 0 ? 0 : 1;

    //_nassert((int)    cols % 4 == 0);
    //#pragma MUST_ITERATE(2,,2);
    //#pragma UNROLL(2);
 
    for (i = 0; i < cols-2; i += 2)
    {
 
        p0 = (_mem4_const(&in_data[i         ]));
        p3 = (_mem4_const(&in_data[i + step  ]));
        p6 = (_mem4_const(&in_data[i + step*2]));

        p1 = p0>>8;       p2 = p0>>16;
        p4 = p3>>8;       p5 = p3>>16;
        p7 = p6>>8;       p8 = p6>>16;

        result = p4 & 0xFFFF;
        result = m0 ? _minu4(result, p0) : result;
        result = m1 ? _minu4(result, p1) : result;
        result = m2 ? _minu4(result, p2) : result;
        result = m3 ? _minu4(result, p3) : result;
        result = m5 ? _minu4(result, p5) : result;
        result = m6 ? _minu4(result, p6) : result;
        result = m7 ? _minu4(result, p7) : result;
        result = m8 ? _minu4(result, p8) : result;

        out_data[i] = (result & 0xFF);
        out_data[i+1] = (result>>8 & 0xFF);
    }
}

void icvDilate_8UC1
(
    const unsigned char *restrict in_data, 
    unsigned char       *restrict out_data, 
    const char          *restrict mask, 
    int cols,
    int step
)
{
    int i;
    unsigned m0, m1, m2, m3, m5, m6, m7, m8;
    unsigned p0, p1, p2, p3, p4, p5, p6, p7, p8;
    unsigned result;

    m0 = mask[0] < 0 ? 0 : 1;
    m1 = mask[1] < 0 ? 0 : 1;
    m2 = mask[2] < 0 ? 0 : 1;
    m3 = mask[3] < 0 ? 0 : 1;
    //m4 = mask[4] < 0 ? 0 : 1;
    m5 = mask[5] < 0 ? 0 : 1;
    m6 = mask[6] < 0 ? 0 : 1;
    m7 = mask[7] < 0 ? 0 : 1;
    m8 = mask[8] < 0 ? 0 : 1;

    //_nassert((int)    cols % 4 == 0);
    //#pragma MUST_ITERATE(2,,2);
    //#pragma UNROLL(2);
 
    for (i = 0; i < cols-2; i += 2)
    {
 
        p0 = (_mem4_const(&in_data[i         ]));
        p3 = (_mem4_const(&in_data[i + step  ]));
        p6 = (_mem4_const(&in_data[i + step*2]));

        p1 = p0>>8;       p2 = p0>>16;
        p4 = p3>>8;       p5 = p3>>16;
        p7 = p6>>8;       p8 = p6>>16;

        result = p4 & 0xFFFF;
        result = m0 ? _maxu4(result, p0) : result;
        result = m1 ? _maxu4(result, p1) : result;
        result = m2 ? _maxu4(result, p2) : result;
        result = m3 ? _maxu4(result, p3) : result;
        result = m5 ? _maxu4(result, p5) : result;
        result = m6 ? _maxu4(result, p6) : result;
        result = m7 ? _maxu4(result, p7) : result;
        result = m8 ? _maxu4(result, p8) : result;

        out_data[i] = (result & 0xFF);
        out_data[i+1] = (result>>8 & 0xFF);
    }
}


static void
icvMorphOp( const void* srcarr, void* dstarr, IplConvKernel* element,
            int iterations, int mop )
{
    CvMat* temp = 0;

    CV_FUNCNAME( "icvMorphOp" );

    __BEGIN__;

    int i, coi1 = 0, coi2 = 0;
    CvMat srcstub, *src = (CvMat*)srcarr;
    CvMat dststub, *dst = (CvMat*)dstarr;
    CvMat *real_dst = 0;
    CvMat *buf = 0;
    CvSize size;
    char kernel[9];
    int type;

    if( !CV_IS_MAT(src) )
        CV_CALL( src = cvGetMat( src, &srcstub, &coi1 ));
    
    if( src != &srcstub )
    {
        srcstub = *src;
        src = &srcstub;
    }

    if( dstarr == srcarr )
        dst = src;
    else
    {
        CV_CALL( dst = cvGetMat( dst, &dststub, &coi2 ));

        if( !CV_ARE_TYPES_EQ( src, dst ))
            CV_ERROR( CV_StsUnmatchedFormats, "" );

        if( !CV_ARE_SIZES_EQ( src, dst ))
            CV_ERROR( CV_StsUnmatchedSizes, "" );
    }

    if( dst != &dststub )
    {
        dststub = *dst;
        dst = &dststub;
    }

	real_dst = dst;
	
    if( coi1 != 0 || coi2 != 0 )
        CV_ERROR( CV_BadCOI, "" );

    type = CV_MAT_TYPE( src->type );
    size = cvGetMatSize( src );

	if(type != CV_8UC1)
		CV_ERROR(CV_StsUnsupportedFormat,"Only 8UC1 is supported currently");
	
    if( iterations == 0 || (element && element->nCols == 1 && element->nRows == 1))
    {
        if( src->data.ptr != dst->data.ptr )
            cvCopy( src, dst );
        EXIT;
    }

    if( element )
    {
    	CV_ERROR(CV_StsUnsupportedFormat,"Can not support customized kerel. The default one is 3x3.");
    }
    else
    {
    	kernel[0]=kernel[1]=kernel[2]=1;
    	kernel[3]=kernel[4]=kernel[5]=1;
    	kernel[6]=kernel[7]=kernel[8]=1;
    }

	buf = cvCloneMat(src);
	src = buf;
 
 	if(mop == 0)
 	{
    	for( i = 0; i < iterations; i++ )
    	{
	       	int r;
        	int offset;
	        for( r = 1; r < size.height-1; r++)
    	    {
    	    	offset = r*dst->step;
        		icvErode_8UC1(src->data.ptr + offset-src->step,
        						dst->data.ptr + offset +1 ,
        						kernel,
        						src->width,
        						src->step);
        	}
        
        	//swap src and dst
        	temp = src;
        	src = dst;
        	dst = temp;
    	}
    }
 	else{
    	for( i = 0; i < iterations; i++ )
    	{
        	int r;
	        for( r = 1; r < size.height-1; r++)
    	    {
        		icvDilate_8UC1(src->data.ptr + (r-1)*src->step,
        						dst->data.ptr + r*dst->step + 1,
        						kernel,
        						src->width,
        						src->step);
        	}
        
        	//swap src and dst
        	temp = src;
        	src = dst;
        	dst = temp;
    	}
    }

	if(real_dst->data.ptr != src->data.ptr)	
		cvCopy(src, real_dst);

   	cvReleaseMat( &buf );
   	
    __END__;

}

CV_IMPL void
cvErode( const void* src, void* dst, IplConvKernel* element, int iterations )
{
    icvMorphOp( src, dst, element, iterations, 0 );
}

CV_IMPL void
cvDilate( const void* src, void* dst, IplConvKernel* element, int iterations )
{
    icvMorphOp( src, dst, element, iterations, 1 );
}


