#pragma once

class HeapSort
{
private:
	void MaxHeapify(long* arr , long i, long length);
	void BuildMaxHeap(long* arr , long length );
	void swap(long* a , long* b );
	
public:
	long * arr;
	long length;
	HeapSort( long* arr = 0, long length = 0);
	~HeapSort(void);
};