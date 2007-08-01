/* file:        ikmeanspush.c
** description: MEX weighted ikmeanspush function.
** author:      Andrea Vedaldi
**/

/* AUTORIGHTS */

#include"mexutils.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<assert.h>

/* driver */
void
mexFunction(int nout, mxArray *out[],
        int nin, const mxArray *in[])
{
    typedef unsigned char data_t ;
    typedef int           acc_t ;
    typedef unsigned int  idx_t ;
    idx_t*    asgn_pt ;
    acc_t*    centers_pt ;
    data_t*   data_pt ;
    /*  mxClassID data_class = mxINT8_CLASS ;*/
    enum {IN_DATA=0,IN_CENTERS} ;
    enum {OUT_ASGN} ;
    int M,N ;
    int K=0 ;

    /** -----------------------------------------------------------------
     **                                               Check the arguments
     ** -------------------------------------------------------------- */
    if (nin != 2) {
        mexErrMsgTxt("Two arguments required.") ;
    } else if (nout > 2) {
        mexErrMsgTxt("Too many output arguments.") ;
    }

    if(mxGetClassID(in[IN_DATA]) != mxUINT8_CLASS) {
        mexErrMsgTxt("DATA must be of class uint8") ;
    }

    if(mxGetClassID(in[IN_CENTERS]) != mxINT32_CLASS) {
        mexErrMsgTxt("DATA must be of class int32") ;
    }

    M = mxGetM(in[IN_DATA]) ;     /* n of components */
    N = mxGetN(in[IN_DATA]) ;     /* n of elements */
    K = mxGetN(in[IN_CENTERS]) ;  /* n of centers */

    if( mxGetM(in[IN_CENTERS]) != M ) {
        mexErrMsgTxt("DATA and CENTERS must have the same number of columns.") ;
    }

    {
        int dims[2] ;
        dims[0] = 1 ;
        dims[1] = N ;
        out[OUT_ASGN] = mxCreateNumericArray(2,dims,mxUINT32_CLASS,mxREAL);
    }

    data_pt    = (data_t*) mxGetPr(in[IN_DATA]) ;
    centers_pt = (acc_t*)  mxGetPr(in[IN_CENTERS]) ;
    asgn_pt    = (idx_t*)  mxGetPr(out[OUT_ASGN]) ;

    vl_ikmeans_push(data_pt, centers_pt, M, N, K, asgn_pt);

    /* 1 based indexing for matlab  */
    int j;
    for(j = 0 ; j < N ; ++j) ++ asgn_pt[j] ;
}