#include "StdAfx.h"
#include "HeapSort.h"

void HeapSort::swap(long* a,long* b){
	long temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void HeapSort::MaxHeapify(long* arr, long i, long length){
	long l = 2 * i + 1;
	long r = 2 * i + 2; 
	long max;

	if( (l < length) && (*(arr+i) < *(arr+l))  ){
		max = l;
	}
	else max = i;
	if(r < length && *(arr+max) < *(arr+r) ){
		max = r;
	}
	if(max != i){
		swap((arr+i), (arr+max) );
		MaxHeapify(arr, max, length);
	}
}


void HeapSort::BuildMaxHeap(long* arr, long length){
	for(long i = (length/2)-1 ; i >= 0 ; i-- ){
		MaxHeapify(arr, i ,length);
	}
}


HeapSort::HeapSort(long* arr,long length){
	BuildMaxHeap(arr, length);
	long size = length;
	for(long i = size-1 ; i > 0; i--){
		swap( arr ,(arr+i));
		length = length-1;
		MaxHeapify(arr,0,length);
	}
}


HeapSort::~HeapSort(void)
{
}
