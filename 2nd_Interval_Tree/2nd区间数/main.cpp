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
		cout << "********���׿α����ϵͳ********" << endl;
		cout << " 1: ����һ���¿�" << endl;
		cout << " 2: ɾ���γ�" << endl;
		cout << " 3: ��ѯ�ض�ʱ����������пγ�����" << endl;
		cout << " 4: ��ӡ���пγ�" << endl;
		cout << "-1: �˳�ϵͳ" << endl;
		cout << endl << "����������: " ;
		cin >> flag;
		switch(flag){
		case 1: 
			z = ( RBnode* )malloc( sizeof( RBnode ) );
			cout << "������γ̱��:" ;
			cin >> z->num;
			cout << "������γ�����:" ;
			cin >> z->name;
			cout << "������γ��½�:" ;
			cin >> z->key;
			cout << "������γ��Ͻ�:" ;
			cin >> z->high;
			T = RB.RBInsert(T,z);
			break;
		case 2:
			int a; int b;
			cout << "������Ҫɾ���γ̵��½�:";
			cin >> a;
			cout << "������Ҫɾ���γ̵��Ͻ�:";
			cin >> b;
			z = RB.findnode(T,a,b);
			if(z){
				T = RB.RBDelete(T,z);
			}
			else{
				cout << "�ÿγ̲�����" << endl;
			}
			break;
		case 3:
			int low; int high;
			cout << "������Ҫ���ҿγ̵��½�:";
			cin >> low;
			cout << "������Ҫ���ҿγ̵��Ͻ�:";
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
