#pragma once
class FastSort
{
private:
	long Partition(long* arr, long p, long r);
	void swap(long* a , long* b );

public:
	long* arr;
	long length;
	FastSort(long* arr = 0,long p = 0, long r = 0);
	~FastSort(void);
};

