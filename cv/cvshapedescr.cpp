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



/* Calculates bounding rectagnle of a point set or retrieves already calculated */
CV_IMPL  CvRect
cvBoundingRect( CvArr* array, int update )
{
    CvSeqReader reader;
    CvRect  rect = { 0, 0, 0, 0 };
    CvContour contour_header;
    CvSeq* ptseq = 0;
    CvSeqBlock block;

    CV_FUNCNAME( "cvBoundingRect" );

    __BEGIN__;

    CvMat stub, *mat = 0;
    int  xmin = 0, ymin = 0, xmax = -1, ymax = -1, i, j, k;
    int calculate = update;

    if( CV_IS_SEQ( array ))
    {
        ptseq = (CvSeq*)array;
        if( !CV_IS_SEQ_POINT_SET( ptseq ))
            CV_ERROR( CV_StsBadArg, "Unsupported sequence type" );

        if( ptseq->header_size < (int)sizeof(CvContour))
        {
            /*if( update == 1 )
                CV_ERROR( CV_StsBadArg, "The header is too small to fit the rectangle, "
                                        "so it could not be updated" );*/
            update = 0;
            calculate = 1;
        }
    }
    else
    {
        CV_CALL( mat = cvGetMat( array, &stub ));
        if( CV_MAT_TYPE(mat->type) == CV_32SC1 ||
            CV_MAT_TYPE(mat->type) == CV_32FC1 )
        {
            CV_CALL( ptseq = cvPointSeqFromMat(
                CV_SEQ_KIND_GENERIC, mat, &contour_header, &block ));
            mat = 0;
        }
        else if( CV_MAT_TYPE(mat->type) != CV_8UC1 &&
                CV_MAT_TYPE(mat->type) != CV_8SC1 )
            CV_ERROR( CV_StsUnsupportedFormat,
                "The image/matrix format is not supported by the function" );
        update = 0;
        calculate = 1;
    }

    if( !calculate )
    {
        rect = ((CvContour*)ptseq)->rect;
        EXIT;
    }

    if( mat )
    {
        CvSize size = cvGetMatSize(mat);
        xmin = size.width;
        ymin = -1;

        for( i = 0; i < size.height; i++ )
        {
            uchar* _ptr = mat->data.ptr + i*mat->step;
            uchar* ptr = (uchar*)cvAlignPtr(_ptr, 4);
            int have_nz = 0, k_min, offset = (int)(ptr - _ptr);
            j = 0;
            offset = MIN(offset, size.width);
            for( ; j < offset; j++ )
                if( _ptr[j] )
                {
                    have_nz = 1;
                    break;
                }
            if( j < offset )
            {
                if( j < xmin )
                    xmin = j;
                if( j > xmax )
                    xmax = j;
            }
            if( offset < size.width )
            {
                xmin -= offset;
                xmax -= offset;
                size.width -= offset;
                j = 0;
                for( ; j <= xmin - 4; j += 4 )
                    if( *((int*)(ptr+j)) )
                        break;
                for( ; j < xmin; j++ )
                    if( ptr[j] )
                    {
                        xmin = j;
                        if( j > xmax )
                            xmax = j;
                        have_nz = 1;
                        break;
                    }
                k_min = MAX(j-1, xmax);
                k = size.width - 1;
                for( ; k > k_min && (k&3) != 3; k-- )
                    if( ptr[k] )
                        break;
                if( k > k_min && (k&3) == 3 )
                {
                    for( ; k > k_min+3; k -= 4 )
                        if( *((int*)(ptr+k-3)) )
                            break;
                }
                for( ; k > k_min; k-- )
                    if( ptr[k] )
                    {
                        xmax = k;
                        have_nz = 1;
                        break;
                    }
                if( !have_nz )
                {
                    j &= ~3;
                    for( ; j <= k - 3; j += 4 )
                        if( *((int*)(ptr+j)) )
                            break;
                    for( ; j <= k; j++ )
                        if( ptr[j] )
                        {
                            have_nz = 1;
                            break;
                        }
                }
                xmin += offset;
                xmax += offset;
                size.width += offset;
            }
            if( have_nz )
            {
                if( ymin < 0 )
                    ymin = i;
                ymax = i;
            }
        }

        if( xmin >= size.width )
            xmin = ymin = 0;
    }
    else if( ptseq->total )
    {   
        int  is_float = CV_SEQ_ELTYPE(ptseq) == CV_32FC2;
        cvStartReadSeq( ptseq, &reader, 0 );

        if( !is_float )
        {
            CvPoint pt;
            /* init values */
            CV_READ_SEQ_ELEM( pt, reader );
            xmin = xmax = pt.x;
            ymin = ymax = pt.y;

            for( i = 1; i < ptseq->total; i++ )
            {            
                CV_READ_SEQ_ELEM( pt, reader );
        
                if( xmin > pt.x )
                    xmin = pt.x;
        
                if( xmax < pt.x )
                    xmax = pt.x;

                if( ymin > pt.y )
                    ymin = pt.y;

                if( ymax < pt.y )
                    ymax = pt.y;
            }
        }
        else
        {
            CvPoint pt;
            Cv32suf v;
            /* init values */
            CV_READ_SEQ_ELEM( pt, reader );
            xmin = xmax = CV_TOGGLE_FLT(pt.x);
            ymin = ymax = CV_TOGGLE_FLT(pt.y);

            for( i = 1; i < ptseq->total; i++ )
            {            
                CV_READ_SEQ_ELEM( pt, reader );
                pt.x = CV_TOGGLE_FLT(pt.x);
                pt.y = CV_TOGGLE_FLT(pt.y);
        
                if( xmin > pt.x )
                    xmin = pt.x;
        
                if( xmax < pt.x )
                    xmax = pt.x;

                if( ymin > pt.y )
                    ymin = pt.y;

                if( ymax < pt.y )
                    ymax = pt.y;
            }

            v.i = CV_TOGGLE_FLT(xmin); xmin = cvFloor(v.f);
            v.i = CV_TOGGLE_FLT(ymin); ymin = cvFloor(v.f);
            /* because right and bottom sides of
               the bounding rectangle are not inclusive
               (note +1 in width and height calculation below),
               cvFloor is used here instead of cvCeil */
            v.i = CV_TOGGLE_FLT(xmax); xmax = cvFloor(v.f);
            v.i = CV_TOGGLE_FLT(ymax); ymax = cvFloor(v.f);
        }
    }

    rect.x = xmin;
    rect.y = ymin;
    rect.width = xmax - xmin + 1;
    rect.height = ymax - ymin + 1;

    if( update )
        ((CvContour*)ptseq)->rect = rect;

    __END__;

    return rect;
}


/* End of file. */
