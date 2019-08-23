#include "StdAfx.h"
#include "InsertSort.h"

InsertSort::InsertSort(long*arr, long length)
{	
	for(long i = 1; i < length ; i++){
		long j = 0;
		while( *(arr+j) < *(arr+i) ){
			j++;
		}// end while
		long temp = *(arr+i);
		long m = 0;
		for(m = i; m > j ; m--){
			*(arr+m) = *(arr+m-1);
		}// end for
		*(arr+m) = temp;
	}// end for
}

InsertSort::~InsertSort(void)
{
}
