#include "StdAfx.h"
#include "RBtree.h"
#include "stdlib.h"
#include <iostream>

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
	else
		(x->parent)->left  = y;
	y->parent = x->parent;
	y->left = x;	x->parent = y;
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
				RBInsertFixup(T,z);
			}
			else{
				if(z == z->parent->right){
					z = z->parent;
					LeftRotate(T,z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				RightRotate(T,z->parent->parent);
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
				RBInsertFixup(T,z);
			}
			else{
				if( z == z->parent->left ){
					RightRotate(T,z->parent);
				}
				z->color = BLACK;
				z->parent->color = RED;
				z->right->color = RED;
				z = z->parent;
				LeftRotate(T,z);
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
		T->key = z->key;
		T->color = BLACK;
		T->left = nil(T);
		T->right = nil(T);
		T->parent = 0;
		return T;
	}
	while( x->left != 0 && x->right != 0){ //非NIL节点
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
	RBInsertFixup(T,z);
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
				LeftRotate(T,x->parent);
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
				RightRotate(T,x->parent);
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
	return T;
} //delete the node y

void RBtree::midprint( RBnode*T){
	if(T->left->left != 0 && T->left->right != 0){
		midprint(T->left);
	}
	cout << T->key << ' ';
	if(T->color == 0) cout << "Black";
	else cout << "Red";
	if(T->right->left != 0 && T->right->right != 0){
		midprint(T->right);
	}
}


RBtree::RBtree(void)
{
}

RBtree::~RBtree(void)
{
}
