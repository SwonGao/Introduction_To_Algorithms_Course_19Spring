#pragma once

struct RBnode{
	RBnode* parent;
	RBnode* left;
	char name[20];
	int num;
	bool color;
	int key;
	int high;
	int max;
	RBnode* right;
};

class RBtree
{
private: 
	RBnode* RBInsertFixup( RBnode* T, RBnode* z ); //right after RBInsert;
	RBnode* RBDeleteFixup( RBnode* T, RBnode* z);
	RBnode* uncle(RBnode* z);

public:
	RBnode* T;
	RBnode* nil(RBnode* x);
	RBnode* RightRotate( RBnode* T, RBnode* x );
	RBnode* LeftRotate( RBnode* T, RBnode* x );
	RBnode* RBInsert( RBnode* T, RBnode* z ); //insert the node z into RBtree T
	RBnode* RBDelete( RBnode* T, RBnode* z ); //delete the node z
	RBnode* RBSuccessor(RBnode* z);
	RBnode* findnode(RBnode* z, int a, int b);
	RBnode* RBtree::IntervalSearch(RBnode* T, int low, int high);
	void FindInterval(RBnode* T, int a, int b);
	void midprint(RBnode* T);
	void levelprint(RBnode* T);
	RBtree(void);
	~RBtree(void);
};

