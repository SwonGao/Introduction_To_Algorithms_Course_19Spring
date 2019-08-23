#include "StdAfx.h"
#include "RBtree.h"
#include "stdlib.h"
#include <iostream>
#include "queue"
#include "cstdio"

using namespace std;

#define RED true
#define BLACK false

RBnode* RBtree::nil(RBnode* x){
	RBnode* z;
	z =(RBnode*)malloc(sizeof(RBnode));
	z->color = BLACK;
	z->left = 0;
	z->right = 0;
	z->key = 0;
	z->parent = x;
	return(z);
}

RBnode* RBtree::RightRotate( RBnode* T, RBnode* y){
	RBnode* x = y->left;
	y->left = x->right;	(x->right)->parent = y;
	if(y->parent && (y->parent)->right == y)
		(y->parent)->right = x;
	else if(!y->parent){
		T = x;
	}
	else
		(y->parent)->left = y;
	x->parent = y->parent ;
	x->right = y;	y->parent = x;
	x->max = y->max ;
	y->max = max(y->right->max ,max(y->high, y->left->max) );
	return T;
}

RBnode* RBtree::LeftRotate( RBnode* T, RBnode* x ){
	RBnode* y = x->right;
	x->right = y->left;	(y->left)->parent = x;
	if( x->parent && (x->parent)->right == x )
		(x->parent)->right = y;
	else if(!x->parent){
		T = y;
	}
	else if(x == x->parent->left ){
		(x->parent)->left  = y;
	}
	else x->parent->right = y;
	y->parent = x->parent;
	y->left = x;	x->parent = y;
	y->max = x->max;
	x->max = max( max(x->high, x->left->max ), x->right->max );
	return T;
}

RBnode* RBtree::uncle(RBnode* z){
	if ( (z->parent->parent)->right == z->parent)
		return (z->parent->parent)->left ;
	else return (z->parent->parent)->right; 
}

RBnode* RBtree::RBInsertFixup( RBnode* T, RBnode* z ){
	if(z->parent == 0){
		z->color = BLACK;
		return T;
	}
	if(z->parent->parent == 0){
		return T;
	}
	if((z->parent == z->parent->parent->left)){
		if( (z->parent)->color == RED ){
			if( uncle(z)->color = RED ){
				uncle(z)->color = BLACK;
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
					T = RBInsertFixup(T,z);
			}
			else{
				if(z == z->parent->right){
					z = z->parent;
					T = LeftRotate(T,z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				T = RightRotate(T,z->parent->parent);
				z = z->parent;
			}
		}
		// Black do nothing
	}
	else{
		//z->parent is z->parent->parent 's right child
		if( (z->parent)->color == RED ){
			if( uncle(z)->color == RED ){
				uncle(z)->color = BLACK;
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
				T = RBInsertFixup(T,z);
			}
			else{
				if( z == z->parent->left ){
					T = RightRotate(T,z->parent);
				}
				z->color = BLACK;
				z->parent->color = RED;
				z->right->color = RED;
				z = z->parent;
				T = LeftRotate(T,z);
			}
		}
	}
	T->color = BLACK;
	return T;
} //right after RBInsert;

RBnode* RBtree::RBInsert( RBnode* T, RBnode* z ){
	RBnode* y;
	RBnode* x=T;
	if(x == 0){
		T = (RBnode*)malloc(sizeof(RBnode));
		T->num = z->num;
		strcpy(T->name, z->name);
		T->key = z->key;
		T->high = z->high;
		T->color = BLACK;
		T->left = nil(T);
		T->right = nil(T);
		T->parent = 0;
		T->max = T->high;
		return T;
	}
	while( x->left != 0 && x->right != 0){ //非NIL节点
		x->max = max(x->max ,z->max );
		y = x;
		if( z->key < x->key )
			x = x->left ;
		else 
			x = x->right;
	}
	z->parent = y;
	if (y->left == 0 && y->right == 0) 
		T = z; 
	else
		if (z->key < y->key ){
			y->left = z; 
			z->parent = y;
		}
		else{ 
			y->right = z;
			z->parent = y;
		}
		z->left = nil(z);
		z->right = nil(z);
	z->color = RED;
	T = RBInsertFixup(T,z);
	return T;
} //insert the node z into RBtree T

RBnode* RBtree::RBDeleteFixup( RBnode* T, RBnode* x ){
	RBnode* w;
	while(x->parent != 0 && x->color == BLACK){
		if( x == x->parent->left ){
			w = x->parent->right;//兄弟节点
			if( w->color == RED ){
				w->color = BLACK;
				x->parent->color = RED;
				T = LeftRotate(T,x->parent);
				w = x->parent->right;
			}
			else if( w->left->color == RED && w->right->color == RED ){
				w->color = RED;
				x = x->parent;
			}
			else if( w->right->color == BLACK && w->left->color == RED ){
				w->left->color = BLACK;
				w->color = RED;
				T = RightRotate(T,w);
				w = x->parent->right;
			}
			else{
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				T = LeftRotate(T,x->parent);
				x = T;
			}
		}
		else{
			w = x->parent->left;
			if( !(w->left && w->right) ){
				return T;
			}//边界条件
			if( w->color == RED ){
				w->color = BLACK;
				x->parent->color = RED;
				T = RightRotate(T,x->parent);
				w = x->parent->left;
			}
			else if( w->left->color == BLACK && w->right->color == BLACK ){
				w->color = RED;
				x = x->parent;
			}
			else if( w->left->color == BLACK && w->right->color ==RED ){
				w->right->color = BLACK;
				w->color = RED;
				T = LeftRotate(T,w);
				w = x->parent->left;
			}
			else{
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				T = RightRotate(T,x->parent);
				x = T;
			}
		}
	}


	return T;
}

RBnode* RBtree::RBSuccessor(RBnode* z){
	RBnode* x;
	if((z->left->left == 0 && z->left->right == 0) && (z->right->left == 0 && z->right->right == 0))
		return (z->right);
	x = z->right;
	while( !(x->left->left == 0 && x->left->right == 0) ){
		x = x->left;
	}// x 到头
	return x;
}

RBnode* RBtree::RBDelete( RBnode* T, RBnode* z ){
	RBnode* y;
	RBnode* x;
	if( (z->left->left == 0 && z->left->right == 0) || (z->right->left == 0 && z->right->right == 0)){
		y = z;
	}//if case 1 & 2
	else{
		y = RBSuccessor(z);
	}//end if case 3
	//end y
	if( !(y->left->left == 0 && y->left->right ==0) ){
		x = y->left;
	}
	else{
		x = y->right;
	}//end x
	x->parent = y->parent;
	//transplant
	if(y->parent == 0){
		T = x;
	}
	else{
		if( y->parent->left == y){
			y->parent->left = x;
		}
		else{
			y->parent->right = x;
		}
	}
	if( y != z ){
		z->key = y->key;
	}
	if(y->color == BLACK){
		T = RBtree::RBDeleteFixup(T,x);
	}
	RBnode* p = x->parent;
	while(p && p->max == z->max){
		p->max = max(max(p->left->max, p->right->max ), p->high);
		p = p->parent;
	}
	return T;
} //delete the node y

void RBtree::midprint( RBnode*T){
	if(T->left->left != 0 && T->left->right != 0){
		midprint(T->left);
	}
	cout << "课程编号为:" << T->num <<", 课程名字为:" << T->name << "[" << T->key <<", " << T->high << "]";
	cout << endl;
	if(T->right->left != 0 && T->right->right != 0){
		midprint(T->right);
	}
}

void RBtree::levelprint( RBnode* T){
	queue<RBnode*> rel;
	if(!T){
		cout << "当前暂无课表信息" << endl;
		return;
	}
	rel.push(T);
	while(!rel.empty()){
		RBnode* front = rel.front();
		cout << "课程编号为:" << front->num <<", 课程名字为:" << front->name << "[" << front->key <<", " << front->high << "]";
		cout << endl;
		if(front->parent != 0){
		cout << front->color << "  " << (front->parent)->num << endl;
		}
		else 
			cout << front->color << endl;
		rel.pop();
		if(front->left->left != 0 && front->left->right != 0){
			rel.push(front->left);
		}
		if(front->right->left != 0 && front->right->right != 0 ){
			rel.push(front->right);
		}
	}

}

RBnode* RBtree::IntervalSearch(RBnode* T, int low, int high){
	RBnode* x = T;
	if(T->left == 0 && T->right == 0){
		return 0;
	}
	if( !(T->key > high || T->high < low) )
		cout << "课程编号为:" << x->num <<", 课程名字为:" << x->name << "[" << x->key <<", " << x->high << "]" << endl;
	IntervalSearch(T->left,low,high);
	IntervalSearch(T->right,low,high);
	return 0 ;
	/*
	if( ( x->left != 0 && x->right != 0 ) && (x->key > high || x->high < low) ){
		if( ( x->left->left!= 0 && x->left->right != 0 ) && x->left->max > low ){
			x = x->left;
		}
		else
			x = x->right;
	}
	cout << "课程编号为:" << x->num <<", 课程名字为:" << x->name << "[" << x->key <<", " << x->high << "]";
	cout << endl;
	return x;
	*/
}

RBnode* RBtree::findnode(RBnode* z, int a, int b){
	RBnode* x;
	RBnode* y;
	if(!z) return 0;
	if( z->left == 0 && z->right == 0) 
		return 0;
	else if( z->key == a && z->high == b )
		return z;
	else{
		x = findnode(z->left, a, b);
		y = findnode(z->right, a, b);
		if(x) return x;
		else return y;
	}
}

RBtree::RBtree(void)
{	
}

RBtree::~RBtree(void)
{
}
