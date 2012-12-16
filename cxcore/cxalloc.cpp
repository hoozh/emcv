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
// Copyright (c) 2008-2012, EMCV Project,
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


#include "_cxcore.h"

#ifdef _TMS320C6X

// default <memalign>
static void*
icvDefaultAlloc( size_t size, void* )
{
	return memalign( (CV_MALLOC_ALIGN/8), size);
}
// default <free>
static int
icvDefaultFree( void* ptr, void* )
{
    free(ptr);
    return CV_OK;
}

#else	// _TMS320C6X

// default <malloc>
static void*
icvDefaultAlloc( size_t size, void* )
{
    char *ptr, *ptr0 = (char*)malloc(
        (size_t)(size + CV_MALLOC_ALIGN*((size >= 4096) + 1) + sizeof(char*)));

    if( !ptr0 )
        return 0;

    // align the pointer
    ptr = (char*)cvAlignPtr(ptr0 + sizeof(char*) + 1, CV_MALLOC_ALIGN);
    *(char**)(ptr - sizeof(char*)) = ptr0;

    return ptr;
}
// default <free>
static int
icvDefaultFree( void* ptr, void* )
{
    // Pointer must be aligned by CV_MALLOC_ALIGN
    if( ((size_t)ptr & (CV_MALLOC_ALIGN-1)) != 0 )
        return CV_BADARG_ERR;
    free( *((char**)ptr - 1) );

    return CV_OK;
}

#endif	// _TMS320C6X

// pointers to allocation functions, initially set to default
static CvAllocFunc p_cvAlloc = (CvAllocFunc)icvDefaultAlloc;
static CvFreeFunc p_cvFree = (CvFreeFunc)icvDefaultFree;
static void* p_cvAllocUserData = 0;


CV_IMPL void cvSetMemoryManager( CvAllocFunc alloc_func, CvFreeFunc free_func, void* userdata )
{
    CV_FUNCNAME( "cvSetMemoryManager" );

    __BEGIN__;
    
    if( (alloc_func == 0) ^ (free_func == 0) )
        CV_ERROR( CV_StsNullPtr, "Either both pointers should be NULL or none of them");

    p_cvAlloc = alloc_func ? alloc_func : (CvAllocFunc)icvDefaultAlloc;
    p_cvFree = free_func ? free_func : (CvFreeFunc)icvDefaultFree;
    p_cvAllocUserData = userdata;

    __END__;
}
CV_IMPL  void*  cvAlloc( size_t size )
{
    void* ptr = 0;
    
    CV_FUNCNAME( "cvAlloc" );

    __BEGIN__;

    if( (size_t)size > CV_MAX_ALLOC_SIZE )
        CV_ERROR( CV_StsOutOfRange,
                  "Negative or too large argument of cvAlloc function" );

    ptr = p_cvAlloc( size, p_cvAllocUserData );
    if( !ptr )
        CV_ERROR( CV_StsNoMem, "Out of memory" );

    __END__;

    return ptr;
}


CV_IMPL  void  cvFree_( void* ptr )
{
    CV_FUNCNAME( "cvFree_" );

    __BEGIN__;

    if( ptr )
    {
        CVStatus status = p_cvFree( ptr, p_cvAllocUserData );
        if( status < 0 )
            CV_ERROR( status, "Deallocation error" );
    }

    __END__;
}

/* End of file. */

