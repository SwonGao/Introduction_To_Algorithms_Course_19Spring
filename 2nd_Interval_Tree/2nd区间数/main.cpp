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
	RBnode* z;
	int flag = 0;
	while(flag != -1){
		cout << "********简易课表管理系统********" << endl;
		cout << " 1: 插入一门新课" << endl;
		cout << " 2: 删除课程" << endl;
		cout << " 3: 查询特定时间区间的所有课程名称" << endl;
		cout << " 4: 打印所有课程" << endl;
		cout << "-1: 退出系统" << endl;
		cout << endl << "请输入数字: " ;
		cin >> flag;
		switch(flag){
		case 1: 
			z = ( RBnode* )malloc( sizeof( RBnode ) );
			cout << "请输入课程编号:" ;
			cin >> z->num;
			cout << "请输入课程名字:" ;
			cin >> z->name;
			cout << "请输入课程下界:" ;
			cin >> z->key;
			cout << "请输入课程上界:" ;
			cin >> z->high;
			T = RB.RBInsert(T,z);
			break;
		case 2:
			int a; int b;
			cout << "请输入要删除课程的下界:";
			cin >> a;
			cout << "请输入要删除课程的上界:";
			cin >> b;
			z = RB.findnode(T,a,b);
			if(z){
				T = RB.RBDelete(T,z);
			}
			else{
				cout << "该课程不存在" << endl;
			}
			break;
		case 3:
			int low; int high;
			cout << "请输入要查找课程的下界:";
			cin >> low;
			cout << "请输入要查找课程的上界:";
			cin >> high;
			RB.IntervalSearch(T,low,high);
			break;
		case 4:
			RB.levelprint(T);
			cout << endl;
			RB.midprint(T);
			break;
		case -1: exit(0);
		}
	}
	/*
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
	*/
	system("pause");
	return;
}
