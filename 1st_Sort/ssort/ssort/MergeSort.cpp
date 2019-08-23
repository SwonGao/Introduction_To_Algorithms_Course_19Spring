#include "StdAfx.h"
#include <stdlib.h>
#include "MergeSort.h"

#define MAX 1000010
long left[MAX];
long right[MAX];

void MergeSort::Merge(long* A, long p, long q, long r){
	long n1 = q-p+1;
	long n2 = r-q;
	long i,j;
	for(i=0; i < n1+1; i++){
		*(left+i) = *(A+p+i);
	}
	for(j=0; j< n2+1; j++){
		*(right+j) = *(A+q+j+1);
	}
	left[n1] = 2147483647;
	right[n2] = left[n1];
	i = 0; 
	j = 0;
	for(long k=p; k<= r ; k++){
		if( left[i] <= right[j] ){
			A[k] = left[i];
			i++;
		}
		else{
			A[k] = right[j];
			j++;
		}
	}
}

MergeSort::MergeSort(long*A, long p ,long r){
	if(p<r){
		long q = (p+r)/2;
		MergeSort(A,p,q);
		MergeSort(A,q+1,r);
		Merge(A,p,q,r);
	}
}


MergeSort::~MergeSort(void){
}
