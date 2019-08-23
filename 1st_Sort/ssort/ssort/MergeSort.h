#pragma once

class MergeSort
{
private: 
	void Merge(long* A, long p, long q, long r);

public:
	long* A;
	long length;
	MergeSort(long* A = 0, long p = 0, long r = 0);
	~MergeSort(void);
};

