#include "StdAfx.h"
#include "FastSort.h"

void FastSort::swap(long* a,long* b){
	long temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
//Partition(arr,0,length);
long FastSort::Partition(long* arr, long p, long r){
	long x = arr[r];
	long i = p - 1;
	for(long j = p ; j <= r-1 ; j++){
		if (arr[j] <= x){
			i++;
			swap( (arr+i),(arr+j));
		}
	}
	swap(arr+i+1, arr+r);
	return (i+1);
}

FastSort::FastSort(long* arr, long p, long r){
	if(p<r){
		long q = Partition(arr, p ,r);
		FastSort(arr, p, q-1);
		FastSort(arr, q+1, r);
	}
}


FastSort::~FastSort(void)
{
}
