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
#include "_cxcore.h"

static IplROI* icvCreateROI( int coi, int xOffset, int yOffset, int width, int height )
{
    IplROI *roi = 0;

    CV_FUNCNAME( "icvCreateROI" );

    __BEGIN__;

    CV_CALL( roi = (IplROI*)cvAlloc( sizeof(*roi)));

    roi->coi = coi;
    roi->xOffset = xOffset;
    roi->yOffset = yOffset;
    roi->width = width;
    roi->height = height;
    __END__;

    return roi;
}


static  void
icvGetColorModel( int nchannels, char** colorModel, char** channelSeq )
{
    static char* tab[][2] =
    {
        {"GRAY", "GRAY"},
        {"",""},
        {"RGB","BGR"},
        {"RGB","BGRA"}
    };

    nchannels--;
    *colorModel = *channelSeq = "";

    if( (unsigned)nchannels <= 3 )
    {
        *colorModel = tab[nchannels][0];
        *channelSeq = tab[nchannels][1];
    }
}

// create IplImage header
CV_IMPL IplImage *
cvCreateImageHeader( CvSize size, int depth, int channels )
{
    IplImage *img = 0;

    CV_FUNCNAME( "cvCreateImageHeader" );

    __BEGIN__;

    CV_CALL( img = (IplImage *)cvAlloc( sizeof( *img )));
    CV_CALL( cvInitImageHeader( img, size, depth, channels, IPL_ORIGIN_TL,
                                    CV_DEFAULT_IMAGE_ROW_ALIGN ));

    __END__;

    if( cvGetErrStatus() < 0 && img )
        cvReleaseImageHeader( &img );

    return img;
}


// create IplImage header and allocate underlying data
CV_IMPL IplImage *
cvCreateImage( CvSize size, int depth, int channels )
{
    IplImage *img = 0;

    CV_FUNCNAME( "cvCreateImage" );

    __BEGIN__;

    CV_CALL( img = cvCreateImageHeader( size, depth, channels ));
    assert( img );
    CV_CALL( cvCreateData( img ));

    __END__;

    if( cvGetErrStatus() < 0 )
        cvReleaseImage( &img );

    return img;
}


// initalize IplImage header, allocated by the user
CV_IMPL IplImage*
cvInitImageHeader( IplImage * image, CvSize size, int depth,
                   int channels, int origin, int align )
{
    IplImage* result = 0;

    CV_FUNCNAME( "cvInitImageHeader" );

    __BEGIN__;

    char *colorModel, *channelSeq;

    if( !image )
        CV_ERROR( CV_HeaderIsNull, "null pointer to header" );

    memset( image, 0, sizeof( *image ));
    image->nSize = sizeof( *image );

    CV_CALL( icvGetColorModel( channels, &colorModel, &channelSeq ));
    strncpy( image->colorModel, colorModel, 4 );
    strncpy( image->channelSeq, channelSeq, 4 );

    if( size.width < 0 || size.height < 0 )
        CV_ERROR( CV_BadROISize, "Bad input roi" );

    if( (depth != (int)IPL_DEPTH_1U && depth != (int)IPL_DEPTH_8U &&
         depth != (int)IPL_DEPTH_8S && depth != (int)IPL_DEPTH_16U &&
         depth != (int)IPL_DEPTH_16S && depth != (int)IPL_DEPTH_32S &&
         depth != (int)IPL_DEPTH_32F && depth != (int)IPL_DEPTH_64F) ||
         channels < 0 )
        CV_ERROR( CV_BadDepth, "Unsupported format" );
    if( origin != CV_ORIGIN_BL && origin != CV_ORIGIN_TL )
        CV_ERROR( CV_BadOrigin, "Bad input origin" );

    if( align != 4 && align != 8 )
        CV_ERROR( CV_BadAlign, "Bad input align" );

    image->width = size.width;
    image->height = size.height;

    if( image->roi )
    {
        image->roi->coi = 0;
        image->roi->xOffset = image->roi->yOffset = 0;
        image->roi->width = size.width;
        image->roi->height = size.height;
    }

    image->nChannels = MAX( channels, 1 );
    image->depth = depth;
    image->align = align;
    image->widthStep = (((image->width * image->nChannels *
         (image->depth & ~IPL_DEPTH_SIGN) + 7)/8)+ align - 1) & (~(align - 1));
    image->origin = origin;
    image->imageSize = image->widthStep * image->height;

    result = image;

    __END__;

    return result;
}


CV_IMPL void
cvReleaseImageHeader( IplImage** image )
{
    CV_FUNCNAME( "cvReleaseImageHeader" );

    __BEGIN__;

    if( !image )
        CV_ERROR( CV_StsNullPtr, "" );

    if( *image )
    {
        IplImage* img = *image;
        *image = 0;
        
        cvFree( &img->roi );
        cvFree( &img );
    }
    __END__;
}


CV_IMPL void
cvReleaseImage( IplImage ** image )
{
    CV_FUNCNAME( "cvReleaseImage" );

    __BEGIN__

    if( !image )
        CV_ERROR( CV_StsNullPtr, "" );

    if( *image )
    {
        IplImage* img = *image;
        *image = 0;
        
        cvReleaseData( img );
        cvReleaseImageHeader( &img );
    }

    __END__;
}




/****************************************************************************************\
*                               CvMat creation and basic operations                      *
\****************************************************************************************/

// Creates CvMat and underlying data
CV_IMPL CvMat*
cvCreateMat( int height, int width, int type )
{
    CvMat* arr = 0;

    CV_FUNCNAME( "cvCreateMat" );
    
    __BEGIN__;

    CV_CALL( arr = cvCreateMatHeader( height, width, type ));
    CV_CALL( cvCreateData( arr ));

    __END__;

    if( cvGetErrStatus() < 0 )
        cvReleaseMat( &arr );

    return arr;
}


static void icvCheckHuge( CvMat* arr )
{
    if( (int)arr->step*arr->rows > INT_MAX )
        arr->type &= ~CV_MAT_CONT_FLAG;
}

// Creates CvMat header only
CV_IMPL CvMat*
cvCreateMatHeader( int rows, int cols, int type )
{
    CvMat* arr = 0;
    
    CV_FUNCNAME( "cvCreateMatHeader" );

    __BEGIN__;

    int min_step;
    type = CV_MAT_TYPE(type);

    if( rows <= 0 || cols <= 0 )
        CV_ERROR( CV_StsBadSize, "Non-positive width or height" );

    min_step = CV_ELEM_SIZE(type)*cols;
    if( min_step <= 0 )
        CV_ERROR( CV_StsUnsupportedFormat, "Invalid matrix type" );

    CV_CALL( arr = (CvMat*)cvAlloc( sizeof(*arr)));

    arr->step = rows == 1 ? 0 : cvAlign(min_step, CV_DEFAULT_MAT_ROW_ALIGN);
    arr->type = CV_MAT_MAGIC_VAL | type |
                (arr->step == 0 || arr->step == min_step ? CV_MAT_CONT_FLAG : 0);
    arr->rows = rows;
    arr->cols = cols;
    arr->data.ptr = 0;
    arr->refcount = 0;
    arr->hdr_refcount = 1;

    icvCheckHuge( arr );

    __END__;

    if( cvGetErrStatus() < 0 )
        cvReleaseMat( &arr );

    return arr;
}


// Initializes CvMat header, allocated by the user
CV_IMPL CvMat*
cvInitMatHeader( CvMat* arr, int rows, int cols,
                 int type, void* data, int step )
{
    CV_FUNCNAME( "cvInitMatHeader" );
    
    __BEGIN__;

    int mask, pix_size, min_step;

    if( !arr )
        CV_ERROR_FROM_CODE( CV_StsNullPtr );

    if( (unsigned)CV_MAT_DEPTH(type) > CV_DEPTH_MAX )
        CV_ERROR_FROM_CODE( CV_BadNumChannels );

    if( rows <= 0 || cols <= 0 )
        CV_ERROR( CV_StsBadSize, "Non-positive cols or rows" );
 
    type = CV_MAT_TYPE( type );
    arr->type = type | CV_MAT_MAGIC_VAL;
    arr->rows = rows;
    arr->cols = cols;
    arr->data.ptr = (uchar*)data;
    arr->refcount = 0;
    arr->hdr_refcount = 0;

    mask = (arr->rows <= 1) - 1;
    pix_size = CV_ELEM_SIZE(type);
    min_step = arr->cols*pix_size & mask;

    if( step != CV_AUTOSTEP && step != 0 )
    {
        if( step < min_step )
            CV_ERROR_FROM_CODE( CV_BadStep );
        arr->step = step & mask;
    }
    else
    {
        arr->step = min_step;
    }

    arr->type = CV_MAT_MAGIC_VAL | type |
                (arr->step == min_step ? CV_MAT_CONT_FLAG : 0);

    icvCheckHuge( arr );

    __END__;

    return arr;
}


// Deallocates the CvMat structure and underlying data
CV_IMPL void
cvReleaseMat( CvMat** array )
{
    CV_FUNCNAME( "cvReleaseMat" );
    
    __BEGIN__;

    if( !array )
        CV_ERROR_FROM_CODE( CV_HeaderIsNull );

    if( *array )
    {
        CvMat* arr = *array;
        
        if( !CV_IS_MAT_HDR(arr) && !CV_IS_MATND_HDR(arr) )
            CV_ERROR_FROM_CODE( CV_StsBadFlag );

        *array = 0;

        cvDecRefData( arr );
        cvFree( &arr );
    }

    __END__;
}



// Creates a copy of matrix
CV_IMPL CvMat*
cvCloneMat( const CvMat* src )
{
    CvMat* dst = 0;
    CV_FUNCNAME( "cvCloneMat" );

    __BEGIN__;

    if( !CV_IS_MAT_HDR( src ))
        CV_ERROR( CV_StsBadArg, "Bad CvMat header" );

    CV_CALL( dst = cvCreateMatHeader( src->rows, src->cols, src->type ));

    if( src->data.ptr )
    {
        CV_CALL( cvCreateData( dst ));
        CV_CALL( cvCopy( src, dst ));
    }

    __END__;

    return dst;
}

// Deallocates array's data
CV_IMPL void
cvReleaseData( CvArr* arr )
{
    CV_FUNCNAME( "cvReleaseData" );
    
    __BEGIN__;

    if( CV_IS_MAT_HDR( arr ) || CV_IS_MATND_HDR( arr ))
    {
        CvMat* mat = (CvMat*)arr;
        cvDecRefData( mat );
    }
    else if( CV_IS_IMAGE_HDR( arr ))
    {
        IplImage* img = (IplImage*)arr;

        char* ptr = img->imageDataOrigin;
        img->imageData = img->imageDataOrigin = 0;
        cvFree( &ptr );
    }
    else
    {
        CV_ERROR( CV_StsBadArg, "unrecognized or unsupported array type" );
    }

    __END__;
}



/****************************************************************************************\
*                          Common for multiple array types operations                    *
\****************************************************************************************/

// Allocates underlying array data
CV_IMPL void
cvCreateData( CvArr* arr )
{
    CV_FUNCNAME( "cvCreateData" );
    
    __BEGIN__;

    if( CV_IS_MAT_HDR( arr ))
    {
        size_t step, total_size;
        CvMat* mat = (CvMat*)arr;
        step = mat->step;

        if( mat->data.ptr != 0 )
            CV_ERROR( CV_StsError, "Data is already allocated" );

        if( step == 0 )
            step = CV_ELEM_SIZE(mat->type)*mat->cols;

        total_size = step*mat->rows + sizeof(int) + CV_MALLOC_ALIGN;
        CV_CALL( mat->refcount = (int*)cvAlloc( (size_t)total_size ));
        mat->data.ptr = (uchar*)cvAlignPtr( mat->refcount + 1, CV_MALLOC_ALIGN );
        *mat->refcount = 1;
    }
    else if( CV_IS_IMAGE_HDR(arr))
    {
        IplImage* img = (IplImage*)arr;

        if( img->imageData != 0 )
            CV_ERROR( CV_StsError, "Data is already allocated" );

        CV_CALL( img->imageData = img->imageDataOrigin = 
                    (char*)cvAlloc( (size_t)img->imageSize ));
    }
    else if( CV_IS_MATND_HDR( arr ))
    {
        CvMatND* mat = (CvMatND*)arr;
        int i;
        size_t total_size = CV_ELEM_SIZE(mat->type);

        if( mat->data.ptr != 0 )
            CV_ERROR( CV_StsError, "Data is already allocated" );

        if( CV_IS_MAT_CONT( mat->type ))
        {
            total_size = (size_t)mat->dim[0].size*(mat->dim[0].step != 0 ?
                         mat->dim[0].step : total_size);
        }
        else
        {
            for( i = mat->dims - 1; i >= 0; i-- )
            {
                size_t size = (size_t)mat->dim[i].step*mat->dim[i].size;

                if( total_size < size )
                    total_size = size;
            }
        }
        
        CV_CALL( mat->refcount = (int*)cvAlloc( total_size +
                                        sizeof(int) + CV_MALLOC_ALIGN ));
        mat->data.ptr = (uchar*)cvAlignPtr( mat->refcount + 1, CV_MALLOC_ALIGN );
        *mat->refcount = 1;
    }
    else
    {
        CV_ERROR( CV_StsBadArg, "unrecognized or unsupported array type" );
    }

    __END__;
}

/****************************************************************************************\
*                             Conversion to CvMat or IplImage                            *
\****************************************************************************************/

// convert array (CvMat or IplImage) to CvMat
CV_IMPL CvMat*
cvGetMat( const CvArr* array, CvMat* mat,
          int* pCOI, int allowND )
{
    CvMat* result = 0;
    CvMat* src = (CvMat*)array;
    int coi = 0;
    
    CV_FUNCNAME( "cvGetMat" );

    __BEGIN__;

    if( !mat || !src )
        CV_ERROR( CV_StsNullPtr, "NULL array pointer is passed" );

    if( CV_IS_MAT_HDR(src))
    {
        if( !src->data.ptr )
            CV_ERROR( CV_StsNullPtr, "The matrix has NULL data pointer" );
        
        result = (CvMat*)src;
    }
    else if( CV_IS_IMAGE_HDR(src) )
    {
        const IplImage* img = (const IplImage*)src;
        int depth, order;

        if( img->imageData == 0 )
            CV_ERROR( CV_StsNullPtr, "The image has NULL data pointer" );

        depth = icvIplToCvDepth( img->depth );
        if( depth < 0 )
            CV_ERROR_FROM_CODE( CV_BadDepth );

        order = img->dataOrder & (img->nChannels > 1 ? -1 : 0);

        if( img->roi )
        {
            if( order == IPL_DATA_ORDER_PLANE )
            {
                int type = depth;

                if( img->roi->coi == 0 )
                    CV_ERROR( CV_StsBadFlag,
                    "Images with planar data layout should be used with COI selected" );

                CV_CALL( cvInitMatHeader( mat, img->roi->height,
                                   img->roi->width, type,
                                   img->imageData + (img->roi->coi-1)*img->imageSize +
                                   img->roi->yOffset*img->widthStep +
                                   img->roi->xOffset*CV_ELEM_SIZE(type),
                                   img->widthStep ));
            }
            else /* pixel order */
            {
                int type = CV_MAKETYPE( depth, img->nChannels );
                coi = img->roi->coi;

                if( img->nChannels > CV_CN_MAX )
                    CV_ERROR( CV_BadNumChannels,
                        "The image is interleaved and has over CV_CN_MAX channels" );

                CV_CALL( cvInitMatHeader( mat, img->roi->height, img->roi->width,
                                          type, img->imageData +
                                          img->roi->yOffset*img->widthStep +
                                          img->roi->xOffset*CV_ELEM_SIZE(type),
                                          img->widthStep ));
            }
        }
        else
        {
            int type = CV_MAKETYPE( depth, img->nChannels );

            if( order != IPL_DATA_ORDER_PIXEL )
                CV_ERROR( CV_StsBadFlag, "Pixel order should be used with coi == 0" );

            CV_CALL( cvInitMatHeader( mat, img->height, img->width, type,
                                      img->imageData, img->widthStep ));
        }

        result = mat;
    }
    else if( allowND && CV_IS_MATND_HDR(src) )
    {
        CvMatND* matnd = (CvMatND*)src;
        int i;
        int size1 = matnd->dim[0].size, size2 = 1;
        
        if( !src->data.ptr )
            CV_ERROR( CV_StsNullPtr, "Input array has NULL data pointer" );

        if( !CV_IS_MAT_CONT( matnd->type ))
            CV_ERROR( CV_StsBadArg, "Only continuous nD arrays are supported here" );

        if( matnd->dims > 2 )
            for( i = 1; i < matnd->dims; i++ )
                size2 *= matnd->dim[i].size;
        else
            size2 = matnd->dims == 1 ? 1 : matnd->dim[1].size;

        mat->refcount = 0;
        mat->hdr_refcount = 0;
        mat->data.ptr = matnd->data.ptr;
        mat->rows = size1;
        mat->cols = size2;
        mat->type = CV_MAT_TYPE(matnd->type) | CV_MAT_MAGIC_VAL | CV_MAT_CONT_FLAG;
        mat->step = size2*CV_ELEM_SIZE(matnd->type);
        mat->step &= size1 > 1 ? -1 : 0;

        icvCheckHuge( mat );
        result = mat;
    }
    else
    {
        CV_ERROR( CV_StsBadFlag, "Unrecognized or unsupported array type" );
    }

    __END__;

    if( pCOI )
        *pCOI = coi;

    return result;
}

// convert array (CvMat or IplImage) to IplImage
CV_IMPL IplImage*
cvGetImage( const CvArr* array, IplImage* img )
{
    IplImage* result = 0;
    const IplImage* src = (const IplImage*)array;
    
    CV_FUNCNAME( "cvGetImage" );

    __BEGIN__;

    int depth;

    if( !img )
        CV_ERROR_FROM_CODE( CV_StsNullPtr );

    if( !CV_IS_IMAGE_HDR(src) )
    {
        const CvMat* mat = (const CvMat*)src;
        
        if( !CV_IS_MAT_HDR(mat))
            CV_ERROR_FROM_CODE( CV_StsBadFlag );

        if( mat->data.ptr == 0 )
            CV_ERROR_FROM_CODE( CV_StsNullPtr );

        depth = cvCvToIplDepth(mat->type);

        cvInitImageHeader( img, cvSize(mat->cols, mat->rows),
                           depth, CV_MAT_CN(mat->type) );
        cvSetData( img, mat->data.ptr, mat->step );

        result = img;
    }
    else
    {
        result = (IplImage*)src;
    }

    __END__;

    return result;
}

// Assigns external data to array
CV_IMPL void
cvSetData( CvArr* arr, void* data, int step )
{
    CV_FUNCNAME( "cvSetData" );

    __BEGIN__;

    int pix_size, min_step;

    if( CV_IS_MAT_HDR(arr) || CV_IS_MATND_HDR(arr) )
        cvReleaseData( arr );

    if( CV_IS_MAT_HDR( arr ))
    {
        CvMat* mat = (CvMat*)arr;
    
        int type = CV_MAT_TYPE(mat->type);
        pix_size = CV_ELEM_SIZE(type);
        min_step = mat->cols*pix_size & ((mat->rows <= 1) - 1);

        if( step != CV_AUTOSTEP )
        {
            if( step < min_step && data != 0 )
                CV_ERROR_FROM_CODE( CV_BadStep );
            mat->step = step & ((mat->rows <= 1) - 1);
        }
        else
        {
            mat->step = min_step;
        }

        mat->data.ptr = (uchar*)data;
        mat->type = CV_MAT_MAGIC_VAL | type |
                    (mat->step==min_step ? CV_MAT_CONT_FLAG : 0);
        icvCheckHuge( mat );
    }
    else if( CV_IS_IMAGE_HDR( arr ))
    {
        IplImage* img = (IplImage*)arr;
    
        pix_size = ((img->depth & 255) >> 3)*img->nChannels;
        min_step = img->width*pix_size;

        if( step != CV_AUTOSTEP && img->height > 1 )
        {
            if( step < min_step && data != 0 )
                CV_ERROR_FROM_CODE( CV_BadStep );
            img->widthStep = step;
        }
        else
        {
            img->widthStep = min_step;
        }

        img->imageSize = img->widthStep * img->height;
        img->imageData = img->imageDataOrigin = (char*)data;

        if( (((int)(size_t)data | step) & 7) == 0 &&
            cvAlign(img->width * pix_size, 8) == step )
        {
            img->align = 8;
        }
        else
        {
            img->align = 4;
        }
    }
    else if( CV_IS_MATND_HDR( arr ))
    {
        CvMatND* mat = (CvMatND*)arr;
        int i;
        int cur_step;
    
        if( step != CV_AUTOSTEP )
            CV_ERROR( CV_BadStep,
            "For multidimensional array only CV_AUTOSTEP is allowed here" );

        mat->data.ptr = (uchar*)data;
        cur_step = CV_ELEM_SIZE(mat->type);

        for( i = mat->dims - 1; i >= 0; i-- )
        {
            if( cur_step > INT_MAX )
                CV_ERROR( CV_StsOutOfRange, "The array is too big" );
            mat->dim[i].step = (int)cur_step;
            cur_step *= mat->dim[i].size;
        }
    }
    else
    {
        CV_ERROR( CV_StsBadArg, "unrecognized or unsupported array type" );
    }

    __END__;
}


// Retrieves essential information about image ROI or CvMat data
CV_IMPL void
cvGetRawData( const CvArr* arr, uchar** data, int* step, CvSize* roi_size )
{
    CV_FUNCNAME( "cvGetRawData" );

    __BEGIN__;

    if( CV_IS_MAT( arr ))
    {
        CvMat *mat = (CvMat*)arr;

        if( step )
            *step = mat->step;

        if( data )
            *data = mat->data.ptr;

        if( roi_size )
            *roi_size = cvGetMatSize( mat );
    }
    else if( CV_IS_IMAGE( arr ))
    {
        IplImage* img = (IplImage*)arr;

        if( step )
            *step = img->widthStep;

        if( data )
            CV_CALL( *data = cvPtr2D( img, 0, 0 ));

        if( roi_size )
        {
            if( img->roi )
            {
                *roi_size = cvSize( img->roi->width, img->roi->height );
            }
            else
            {
                *roi_size = cvSize( img->width, img->height );
            }
        }
    }
    else if( CV_IS_MATND( arr ))
    {
        CvMatND* mat = (CvMatND*)arr;

        if( !CV_IS_MAT_CONT( mat->type ))
            CV_ERROR( CV_StsBadArg, "Only continuous nD arrays are supported here" );

        if( data )
            *data = mat->data.ptr;

        if( roi_size || step )
        {
            int i, size1 = mat->dim[0].size, size2 = 1;

            if( mat->dims > 2 )
                for( i = 1; i < mat->dims; i++ )
                    size1 *= mat->dim[i].size;
            else
                size2 = mat->dim[1].size;

            if( roi_size )
            {
                roi_size->width = size2;
                roi_size->height = size1;
            }

            if( step )
                *step = size1 == 1 ? 0 : mat->dim[0].step;
        }
    }
    else
    {
        CV_ERROR( CV_StsBadArg, "unrecognized or unsupported array type" );
    }

    __END__;
}



// Returns pointer to specified element of array (linear index is used)
CV_IMPL  uchar*
cvPtr1D( const CvArr* arr, int idx, int* _type )
{
    uchar* ptr = 0;
    
    CV_FUNCNAME( "cvPtr1D" );

    __BEGIN__;

    if( CV_IS_MAT( arr ))
    {
        CvMat* mat = (CvMat*)arr;

        int type = CV_MAT_TYPE(mat->type);
        int pix_size = CV_ELEM_SIZE(type);

        if( _type )
            *_type = type;
        
        // the first part is mul-free sufficient check
        // that the index is within the matrix
        if( (unsigned)idx >= (unsigned)(mat->rows + mat->cols - 1) &&
            (unsigned)idx >= (unsigned)(mat->rows*mat->cols))
            CV_ERROR( CV_StsOutOfRange, "index is out of range" );

        if( CV_IS_MAT_CONT(mat->type))
        {
            ptr = mat->data.ptr + (size_t)idx*pix_size;
        }
        else
        {
            int row, col;
            if( mat->cols == 1 )
                row = idx, col = 0;
            else
                row = idx/mat->cols, col = idx - row*mat->cols;
            ptr = mat->data.ptr + (size_t)row*mat->step + col*pix_size;
        }
    }
    else if( CV_IS_IMAGE_HDR( arr ))
    {
        IplImage* img = (IplImage*)arr;
        int width = !img->roi ? img->width : img->roi->width;
        int y = idx/width, x = idx - y*width;

        ptr = cvPtr2D( arr, y, x, _type );
    }
    else if( CV_IS_MATND( arr ))
    {
        CvMatND* mat = (CvMatND*)arr;
        int j, type = CV_MAT_TYPE(mat->type);
        size_t size = mat->dim[0].size;

        if( _type )
            *_type = type;

        for( j = 1; j < mat->dims; j++ )
            size *= mat->dim[j].size;

        if((unsigned)idx >= (unsigned)size )
            CV_ERROR( CV_StsOutOfRange, "index is out of range" );

        if( CV_IS_MAT_CONT(mat->type))
        {
            int pix_size = CV_ELEM_SIZE(type);
            ptr = mat->data.ptr + (size_t)idx*pix_size;
        }
        else
        {
            ptr = mat->data.ptr;
            for( j = mat->dims - 1; j >= 0; j-- )
            {
                int sz = mat->dim[j].size;
                if( sz )
                {
                    int t = idx/sz;
                    ptr += (idx - t*sz)*mat->dim[j].step;
                    idx = t;
                }
            }
        }
    }
    else if( CV_IS_SPARSE_MAT( arr ))
    {
        CV_ERROR( CV_StsBadArg, "do not support sparse mat now" );
    }
    else
    {
        CV_ERROR( CV_StsBadArg, "unrecognized or unsupported array type" );
    }

    __END__;

    return ptr;
}


// Returns pointer to specified element of 2d array
CV_IMPL  uchar*
cvPtr2D( const CvArr* arr, int y, int x, int* _type )
{
    uchar* ptr = 0;
    
    CV_FUNCNAME( "cvPtr2D" );

    __BEGIN__;

    if( CV_IS_MAT( arr ))
    {
        CvMat* mat = (CvMat*)arr;
        int type;

        if( (unsigned)y >= (unsigned)(mat->rows) ||
            (unsigned)x >= (unsigned)(mat->cols) )
            CV_ERROR( CV_StsOutOfRange, "index is out of range" );

        type = CV_MAT_TYPE(mat->type);
        if( _type )
            *_type = type;

        ptr = mat->data.ptr + (size_t)y*mat->step + x*CV_ELEM_SIZE(type);
    }
    else if( CV_IS_IMAGE( arr ))
    {
        IplImage* img = (IplImage*)arr;
        int pix_size = (img->depth & 255) >> 3;
        int width, height;
        ptr = (uchar*)img->imageData;

        if( img->dataOrder == 0 )
            pix_size *= img->nChannels;

        if( img->roi )
        {
            width = img->roi->width;
            height = img->roi->height;

            ptr += img->roi->yOffset*img->widthStep +
                   img->roi->xOffset*pix_size;

            if( img->dataOrder )
            {
                int coi = img->roi->coi;
                if( !coi )
                    CV_ERROR( CV_BadCOI,
                        "COI must be non-null in case of planar images" );
                ptr += (coi - 1)*img->imageSize;
            }
        }
        else
        {
            width = img->width;
            height = img->height;
        }

        if( (unsigned)y >= (unsigned)height ||
            (unsigned)x >= (unsigned)width )
            CV_ERROR( CV_StsOutOfRange, "index is out of range" );

        ptr += y*img->widthStep + x*pix_size;

        if( _type )
        {
            int type = icvIplToCvDepth(img->depth);
            if( type < 0 || (unsigned)(img->nChannels - 1) > 3 )
                CV_ERROR( CV_StsUnsupportedFormat, "" );

            *_type = CV_MAKETYPE( type, img->nChannels );
        }
    }
    else if( CV_IS_MATND( arr ))
    {
        CvMatND* mat = (CvMatND*)arr;

        if( mat->dims != 2 || 
            (unsigned)y >= (unsigned)(mat->dim[0].size) ||
            (unsigned)x >= (unsigned)(mat->dim[1].size) )
            CV_ERROR( CV_StsOutOfRange, "index is out of range" );

        ptr = mat->data.ptr + (size_t)y*mat->dim[0].step + x*mat->dim[1].step;
        if( _type )
            *_type = CV_MAT_TYPE(mat->type);
    }
    else if( CV_IS_SPARSE_MAT( arr ))
    {
        CV_ERROR( CV_StsBadArg, "do not support sparse mat now" );
    }
    else
    {
        CV_ERROR( CV_StsBadArg, "unrecognized or unsupported array type" );
    }

    __END__;

    return ptr;
}


// Returns pointer to specified element of 3d array
CV_IMPL  uchar*
cvPtr3D( const CvArr* arr, int z, int y, int x, int* _type )
{
    uchar* ptr = 0;
    
    CV_FUNCNAME( "cvPtr3D" );

    __BEGIN__;

    if( CV_IS_MATND( arr ))
    {
        CvMatND* mat = (CvMatND*)arr;

        if( mat->dims != 3 || 
            (unsigned)z >= (unsigned)(mat->dim[0].size) ||
            (unsigned)y >= (unsigned)(mat->dim[1].size) ||
            (unsigned)x >= (unsigned)(mat->dim[2].size) )
            CV_ERROR( CV_StsOutOfRange, "index is out of range" );

        ptr = mat->data.ptr + (size_t)z*mat->dim[0].step +
              (size_t)y*mat->dim[1].step + x*mat->dim[2].step;

        if( _type )
            *_type = CV_MAT_TYPE(mat->type);
    }
    else if( CV_IS_SPARSE_MAT( arr ))
    {
        CV_ERROR( CV_StsBadArg, "do not support sparse mat now" );
    }
    else
    {
        CV_ERROR( CV_StsBadArg, "unrecognized or unsupported array type" );
    }

    __END__;

    return ptr;
}

// Returns the size of CvMat or IplImage
CV_IMPL CvSize
cvGetSize( const CvArr* arr )
{
    CvSize size = { 0, 0 };

    CV_FUNCNAME( "cvGetSize" );

    __BEGIN__;

    if( CV_IS_MAT_HDR( arr ))
    {
        CvMat *mat = (CvMat*)arr;

        size.width = mat->cols;
        size.height = mat->rows;
    }
    else if( CV_IS_IMAGE_HDR( arr ))
    {
        IplImage* img = (IplImage*)arr;

        if( img->roi )
        {
            size.width = img->roi->width;
            size.height = img->roi->height;
        }
        else
        {
            size.width = img->width;
            size.height = img->height;
        }
    }
    else
    {
        CV_ERROR( CV_StsBadArg, "Array should be CvMat or IplImage" );
    }

    __END__;

    return size;
}

// Selects sub-array (no data is copied)
CV_IMPL  CvMat*
cvGetSubRect( const CvArr* arr, CvMat* submat, CvRect rect )
{
    CvMat* res = 0;
    
    CV_FUNCNAME( "cvGetRect" );

    __BEGIN__;

    CvMat stub, *mat = (CvMat*)arr;

    if( !CV_IS_MAT( mat ))
        CV_CALL( mat = cvGetMat( mat, &stub ));

    if( !submat )
        CV_ERROR( CV_StsNullPtr, "" );

    if( (rect.x|rect.y|rect.width|rect.height) < 0 )
        CV_ERROR( CV_StsBadSize, "" );

    if( rect.x + rect.width > mat->cols ||
        rect.y + rect.height > mat->rows )
        CV_ERROR( CV_StsBadSize, "" );

    {
    /*
    int* refcount = mat->refcount;

    if( refcount )
        ++*refcount;

    cvDecRefData( submat );
    */
    submat->data.ptr = mat->data.ptr + (size_t)rect.y*mat->step +
                       rect.x*CV_ELEM_SIZE(mat->type);
    submat->step = mat->step & (rect.height > 1 ? -1 : 0);
    submat->type = (mat->type & (rect.width < mat->cols ? ~CV_MAT_CONT_FLAG : -1)) |
                   (submat->step == 0 ? CV_MAT_CONT_FLAG : 0);
    submat->rows = rect.height;
    submat->cols = rect.width;
    submat->refcount = 0;
    res = submat;
    }
    
    __END__;

    return res;
}


// Selects array's row span.
CV_IMPL  CvMat*
cvGetRows( const CvArr* arr, CvMat* submat,
           int start_row, int end_row, int delta_row )
{
    CvMat* res = 0;
    
    CV_FUNCNAME( "cvGetRows" );

    __BEGIN__;

    CvMat stub, *mat = (CvMat*)arr;

    if( !CV_IS_MAT( mat ))
        CV_CALL( mat = cvGetMat( mat, &stub ));

    if( !submat )
        CV_ERROR( CV_StsNullPtr, "" );

    if( (unsigned)start_row >= (unsigned)mat->rows ||
        (unsigned)end_row > (unsigned)mat->rows || delta_row <= 0 )
        CV_ERROR( CV_StsOutOfRange, "" );

    {
    /*
    int* refcount = mat->refcount;

    if( refcount )
        ++*refcount;

    cvDecRefData( submat );
    */
    if( delta_row == 1 )
    {
        submat->rows = end_row - start_row;
        submat->step = mat->step & (submat->rows > 1 ? -1 : 0);
    }
    else
    {
        submat->rows = (end_row - start_row + delta_row - 1)/delta_row;
        submat->step = mat->step * delta_row;
    }

    submat->cols = mat->cols;
    submat->step &= submat->rows > 1 ? -1 : 0;
    submat->data.ptr = mat->data.ptr + (size_t)start_row*mat->step;
    submat->type = (mat->type | (submat->step == 0 ? CV_MAT_CONT_FLAG : 0)) &
                   (delta_row != 1 ? ~CV_MAT_CONT_FLAG : -1);
    submat->refcount = 0;
    submat->hdr_refcount = 0;
    res = submat;
    }
    
    __END__;

    return res;
}


// Selects array's column span.
CV_IMPL  CvMat*
cvGetCols( const CvArr* arr, CvMat* submat, int start_col, int end_col )
{
    CvMat* res = 0;
    
    CV_FUNCNAME( "cvGetCols" );

    __BEGIN__;

    CvMat stub, *mat = (CvMat*)arr;

    if( !CV_IS_MAT( mat ))
        CV_CALL( mat = cvGetMat( mat, &stub ));

    if( !submat )
        CV_ERROR( CV_StsNullPtr, "" );

    if( (unsigned)start_col >= (unsigned)mat->cols ||
        (unsigned)end_col > (unsigned)mat->cols )
        CV_ERROR( CV_StsOutOfRange, "" );

    {
    /*
    int* refcount = mat->refcount;

    if( refcount )
        ++*refcount;

    cvDecRefData( submat );
    */
    submat->rows = mat->rows;
    submat->cols = end_col - start_col;
    submat->step = mat->step & (submat->rows > 1 ? -1 : 0);
    submat->data.ptr = mat->data.ptr + (size_t)start_col*CV_ELEM_SIZE(mat->type);
    submat->type = mat->type & (submat->step && submat->cols < mat->cols ?
                                ~CV_MAT_CONT_FLAG : -1);
    submat->refcount = 0;
    submat->hdr_refcount = 0;
    res = submat;
    }
    
    __END__;

    return res;
}


// Selects array diagonal
CV_IMPL  CvMat*
cvGetDiag( const CvArr* arr, CvMat* submat, int diag )
{
    CvMat* res = 0;
    
    CV_FUNCNAME( "cvGetDiag" );

    __BEGIN__;

    CvMat stub, *mat = (CvMat*)arr;
    int len, pix_size; 

    if( !CV_IS_MAT( mat ))
        CV_CALL( mat = cvGetMat( mat, &stub ));

    if( !submat )
        CV_ERROR( CV_StsNullPtr, "" );

    pix_size = CV_ELEM_SIZE(mat->type);

    /*{
    int* refcount = mat->refcount;

    if( refcount )
        ++*refcount;

    cvDecRefData( submat );
    }*/

    if( diag >= 0 )
    {
        len = mat->cols - diag;
        
        if( len <= 0 )
            CV_ERROR( CV_StsOutOfRange, "" );

        len = CV_IMIN( len, mat->rows );
        submat->data.ptr = mat->data.ptr + diag*pix_size;
    }
    else
    {
        len = mat->rows + diag;
        
        if( len <= 0 )
            CV_ERROR( CV_StsOutOfRange, "" );

        len = CV_IMIN( len, mat->cols );
        submat->data.ptr = mat->data.ptr - diag*mat->step;
    }

    submat->rows = len;
    submat->cols = 1;
    submat->step = (mat->step + pix_size) & (submat->rows > 1 ? -1 : 0);
    submat->type = mat->type;
    if( submat->step )
        submat->type &= ~CV_MAT_CONT_FLAG;
    else
        submat->type |= CV_MAT_CONT_FLAG;
    submat->refcount = 0;
    submat->hdr_refcount = 0;
    res = submat;
    
    __END__;

    return res;
}


/****************************************************************************************\
*                      Operations on CvScalar and accessing array elements               *
\****************************************************************************************/

// Converts CvScalar to specified type
CV_IMPL void
cvScalarToRawData( const CvScalar* scalar, void* data, int type, int extend_to_12 )
{
    CV_FUNCNAME( "cvScalarToRawData" );

    type = CV_MAT_TYPE(type);
    
    __BEGIN__;

    int cn = CV_MAT_CN( type );
    int depth = type & CV_MAT_DEPTH_MASK;

    assert( scalar && data );
    if( (unsigned)(cn - 1) >= 4 )
        CV_ERROR( CV_StsOutOfRange, "The number of channels must be 1, 2, 3 or 4" );

    switch( depth )
    {
    case CV_8UC1:
        while( cn-- )
        {
            int t = cvRound( scalar->val[cn] );
            ((uchar*)data)[cn] = CV_CAST_8U(t);
        }
        break;
    case CV_8SC1:
        while( cn-- )
        {
            int t = cvRound( scalar->val[cn] );
            ((char*)data)[cn] = CV_CAST_8S(t);
        }
        break;
    case CV_16UC1:
        while( cn-- )
        {
            int t = cvRound( scalar->val[cn] );
            ((ushort*)data)[cn] = CV_CAST_16U(t);
        }
        break;
    case CV_16SC1:
        while( cn-- )
        {
            int t = cvRound( scalar->val[cn] );
            ((short*)data)[cn] = CV_CAST_16S(t);
        }
        break;
    case CV_32SC1:
        while( cn-- )
            ((int*)data)[cn] = cvRound( scalar->val[cn] );
        break;
    case CV_32FC1:
        while( cn-- )
            ((float*)data)[cn] = (float)(scalar->val[cn]);
        break;
    case CV_64FC1:
        while( cn-- )
            ((double*)data)[cn] = (double)(scalar->val[cn]);
        break;
    default:
        assert(0);
        CV_ERROR_FROM_CODE( CV_BadDepth );
    }

    if( extend_to_12 )
    {
        int pix_size = CV_ELEM_SIZE(type);
        int offset = CV_ELEM_SIZE1(depth)*12;

        do
        {
            offset -= pix_size;
            CV_MEMCPY_AUTO( (char*)data + offset, data, pix_size );
        }
        while( offset > pix_size );
    }

    __END__;
}


// Converts data of specified type to CvScalar
CV_IMPL void
cvRawDataToScalar( const void* data, int flags, CvScalar* scalar )
{
    CV_FUNCNAME( "cvRawDataToScalar" );
    
    __BEGIN__;

    int cn = CV_MAT_CN( flags );

    assert( scalar && data );
    
    if( (unsigned)(cn - 1) >= 4 )
        CV_ERROR( CV_StsOutOfRange, "The number of channels must be 1, 2, 3 or 4" );

    memset( scalar->val, 0, sizeof(scalar->val));

    switch( CV_MAT_DEPTH( flags ))
    {
    case CV_8U:
        while( cn-- )
            scalar->val[cn] = CV_8TO32F(((uchar*)data)[cn]);
        break;
    case CV_8S:
        while( cn-- )
            scalar->val[cn] = CV_8TO32F(((char*)data)[cn]);
        break;
    case CV_16U:
        while( cn-- )
            scalar->val[cn] = ((ushort*)data)[cn];
        break;
    case CV_16S:
        while( cn-- )
            scalar->val[cn] = ((short*)data)[cn];
        break;
    case CV_32S:
        while( cn-- )
            scalar->val[cn] = ((int*)data)[cn];
        break;
    case CV_32F:
        while( cn-- )
            scalar->val[cn] = ((float*)data)[cn];
        break;
    case CV_64F:
        while( cn-- )
            scalar->val[cn] = ((double*)data)[cn];
        break;
    default:
        assert(0);
        CV_ERROR_FROM_CODE( CV_BadDepth );
    }

    __END__;
}



CV_IMPL IplImage*
cvCloneImage( const IplImage* src )
{
    IplImage* dst = 0;
    CV_FUNCNAME( "cvCloneImage" );

    __BEGIN__;

    if( !CV_IS_IMAGE_HDR( src ))
        CV_ERROR( CV_StsBadArg, "Bad image header" );

    CV_CALL( dst = (IplImage*)cvAlloc( sizeof(*dst)));

    memcpy( dst, src, sizeof(*src));
    dst->imageData = dst->imageDataOrigin = 0;
    dst->roi = 0;

    if( src->roi )
    {
        dst->roi = icvCreateROI( src->roi->coi, src->roi->xOffset,
                      src->roi->yOffset, src->roi->width, src->roi->height );
    }

    if( src->imageData )
    {
        int size = src->imageSize;
        cvCreateData( dst );
        memcpy( dst->imageData, src->imageData, size );
    }
 
    __END__;

    return dst;
}




