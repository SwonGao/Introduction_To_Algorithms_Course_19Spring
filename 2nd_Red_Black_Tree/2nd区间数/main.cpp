#include "stdAfx.h"
#include "RBtree.h"
#include "iostream"

using namespace std;

#define RED true
#define BLACK false

void main()
{
	RBtree RB;
	RBnode* T = 0;
	RB.T = T;
	RBnode* z,y;
	z = (RBnode*)malloc(sizeof(RBnode));
	z->key = 100;
	T = RB.RBInsert(T,z);
		z = (RBnode*)malloc(sizeof(RBnode));
	z->key = 105;
	T = RB.RBInsert(T,z);
	z = (RBnode*)malloc(sizeof(RBnode));
	z->key = 98;
	T = RB.RBInsert(T,z);
	z = (RBnode*)malloc(sizeof(RBnode));
	z->key = 99;
	T = RB.RBInsert(T,z);
	RB.midprint(T);cout << endl;
	T = RB.RBDelete(T,T->left);
	RB.midprint(T);cout << endl;
	T = RB.RBDelete(T,T->left);
	RB.midprint(T);cout << endl;
	T = RB.RBDelete(T,T->right);
	RB.midprint(T);cout << endl;
	system("pause");
	return;
}
