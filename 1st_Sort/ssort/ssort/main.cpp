#include "StdAfx.h"
#include "HeapSort.h"
#include "InsertSort.h"
#include "FastSort.h"
#include "MergeSort.h"
#include "Windows.h"
#include <iostream>

using namespace std;

#define MAX 10
long a[MAX] = {0};
long length = MAX;

void createrandom(long* arr, long length){
	for(long i = 0; i < length;i++){
		arr[i] = rand();
	}
}

void main(){
	createrandom(a, length);

	MergeSort merge;
	merge.A = &a[0];
	merge.length = MAX;

	HeapSort heap;
	heap.arr = &a[0];
	heap.length = MAX;

	InsertSort insert;
	insert.arr = &a[0];
	insert.length = MAX;

	FastSort quick;
	quick.arr = &a[0];
	quick.length = MAX;
	// initialize;
	for(int i = 0; i< 10 ;i ++){
	DWORD start_time =  GetTickCount();
	HeapSort::HeapSort(heap.arr,heap.length);
	DWORD end_time =  GetTickCount();
	for(int i = 0;i< MAX ;i++){
		cout << a[i] << " ";
	}
	cout << "when the size of test set is: " << insert.length << ", the HeapSort's spent time is: " << end_time - start_time << "ms." <<endl;
	// HeapSort

	createrandom(a, length);
	start_time =  GetTickCount();
	InsertSort::InsertSort(insert.arr, insert.length);

	end_time =  GetTickCount();
	for(int i = 0;i< MAX ;i++){
		cout << a[i] << " ";
	}
 	cout << "when the size of test set is: " << insert.length << ", the InsertSort's spent time is: " << end_time - start_time << "ms." <<endl;
	// InsertSort

	createrandom(a, length);
	start_time =  GetTickCount();
	FastSort::FastSort(quick.arr, 0 ,quick.length-1);
	end_time =  GetTickCount();
	for(int i = 0;i< MAX ;i++){
		cout << a[i] << " ";
	}
 	cout << "when the size of test set is: " << insert.length << ", the FastSort's spent time is: " << end_time - start_time << "ms." <<endl;
	// QuickSort
	
	createrandom(a, length);
	start_time =  GetTickCount();
	MergeSort::MergeSort(merge.A, 0, merge.length-1 );
	end_time =  GetTickCount();
	for(int i = 0;i< MAX ;i++){
		cout << a[i]<< " ";
	}
 	cout << "when the size of test set is: " << insert.length << ", the MergeSort's spent time is: " << end_time - start_time << "ms." <<endl << endl;
	// MergeSort
	}
	system("pause");
}