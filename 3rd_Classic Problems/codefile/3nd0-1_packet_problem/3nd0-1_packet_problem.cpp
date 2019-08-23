// 3nd0-1_packet_problem.cpp : �������̨Ӧ�ó������ڵ㡣

#include "stdafx.h"
#include "math.h"
#include "queue"
#include <stdlib.h>
#include <time.h> 
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

typedef struct PriorNode {
	//ע������>�Ż���������Ϊ��׼��Ĭ��ʹ��Ԫ�����͵�<��������ȷ������֮������ȼ���ϵ��
	bool operator <(const struct PriorNode& d)const {
		if (up < d.up)
		{
			return true;
		}
		return false;
	}
	int up;
	int cv;
	int cw;
	bool node;
	int number;
}PriorNode;

// �����ӡ����
void printSolve(int* x, int n){
	int i = 0;
	while(i < n){
		cout << x[i] << "  ";
		i++;
	}
	cout << endl;
}

void getInt(string& s, int* a, int n)
{
	istringstream iss(s);
	int num, res = 0;
	int i = 1;
	while (i<=n) {
		iss >> num;
		a[i-1] = num;
		i++;
	}
}

//=======================================ö�ٷ�====================================================================

//����ö������
void createExhaustion(int numerate[][10], int n){
	int num = (int)pow(2,double(n));
	int index = num/2;
	int i,j,temp,flag;
	for(j = 0; j < n; j++){
		temp = 0;
		flag = 0;
		while(temp<num){
			for(i = temp; i<index+temp; i++){
				if(flag == 0){
					numerate[i][j] = 0;
				}
				else
					numerate[i][j] = 1;
			}
			if(flag == 0) flag++;
			else	flag--;
			temp += index;
		}
		index /= 2;
	}
}

int findsolution(int* numerate, int n, int* v, int* w, int c){
	int value = 0;
	int weigh = 0;
	for(int i = 0 ; i < n ; i++){
		if(numerate[i] == 1){
			value += v[i];
			weigh += w[i];
		}
	}
	if(weigh > c) 
		return (-1);
	else
		return value;
}


//=======================================��̬�滮====================================================================
// ��̬�滮
void Knapsack(int* v, int* w, int c, int n, int m[][100]){
	int jMax;
	int i,j;
	jMax = (int)min(w[n-1]-1,c);
	for(j = 0; j <= jMax; j++){
		m[n-1][j] = 0;
	}
	for(j = w[n-1]; j <= c; j++){
		m[n-1][j] = v[n-1];
	}// m[n][j];
	for(i = n-2; i>0; i--){
		jMax = (int)min(w[i]-1,c);
		for(j = 0; j <= jMax; j++){
			m[i][j] = m[i+1][j];
		}
		for(j = w[i]; j <= c; j++){
			m[i][j] = (int)max( m[i+1][j], m[i+1][j-w[i]] + v[i] );
		}// m[n][j];
	}//��ʱ��i=0 ��������
	if(c>=w[0])
		m[0][c] = (int)max(m[1][c],m[1][c-w[0]]+v[0]);
	else
		m[0][c] = m[1][c];
	//return m;
}

// ��̬�滮Traceback
void Traceback(int* w,int c,int n, int m[][100], int* x){
	int i;
	for(i=0;i<n;i++){
		if(m[i][c] == m[i+1][c]) 
			x[i] = 0;
		else{
			x[i] = 1;
			c -= w[i];
		}
	}
	x[n-1] = ((m[n-1][c])?1:0);
	//return x;
}


//=======================================�Զ����µı���¼��====================================================================

int Lookup(int i, int j, int m[][100],int n, int* v, int* w, int c){
	int jMax;
	if(i<0 || j<0) return -1;
	if(m[i][j]>0 ) return m[i][j];
	//����鵽������	���û�鵽���������ֵ��
	if(i == n-1){
		jMax = (int)min(w[n-1]-1,c);
		if( j <= jMax)	m[n-1][j] = 0;
		else			m[n-1][j] = v[n-1];			
		return m[n-1][j];
	}// ������ʼ����
	else if(i == 0){
		if(c>=w[0])
			m[0][c] = (int)max( (double)Lookup(1,c,m,n,v,w,c) , (double)Lookup(1,c-w[0],m,n,v,w,c) + v[0]);
		else
			m[0][c] = Lookup(1,c,m,n,v,w,c);
		return m[0][c];
	}// �ֿ�����
	else{
		jMax = (int)min(w[i]-1,c);
		if (j <= jMax ) {
			 m[i][j] = Lookup(i+1,j,m,n,v,w,c);
		}
		else
			 m[i][j] = (int)max( (double)Lookup(i+1,j,m,n,v,w,c) , (double)(Lookup(i+1,j-w[i],m,n,v,w,c)+v[i]) );
		return m[i][j];
	}
}

int Memorized(int m[][100], int n,int *v,int *w,int c){
	for (int i = 0; i <= n - 1; i++)
		for (int j = 0; j <= c; j++)
			m[i][j] = -1;
	// ��ѯm[0][c]
	return Lookup(0, c, m,n,v,w,c);
}


//=======================================���ݷ�====================================================================

int KnapBacktrack(int i, int cw,int cv, int bestv, int* temp, int n, int* w,int* v, int* x,int c)
{
	if (i > n-1) {
		if (bestv < cv) {
			bestv = cv;
			for (int j = 0; j < n; x[j] = temp[j++]);
		}
		return bestv;
	}// ���������н�
	else {
		if (cw + w[i] <= c) {
			int sum = 0;
			for (int t = i; t <= n - 1; sum += v[t++]); //�޽�
			if (cv + sum > bestv) {
				temp[i] = 1;
				cw = cw + w[i];
				cv = cv + v[i];
				bestv = KnapBacktrack(i + 1, cw, cv, bestv, temp,n,w,v,x,c);
				cw = cw - w[i];
				cv = cv - v[i];
			}
		}
		int sum = 0;
		for (int t = i + 1; t <= n - 1; sum += v[t++]); //�޽�
		if (cv + sum > bestv) {
			temp[i] = 0;
			bestv = KnapBacktrack(i + 1, cw, cv, bestv, temp,n,w,v,x,c);
		}
	}
	return bestv;
}

void BackTrack_Packet(int n, int* w,int* v, int* x,int c)
{
	int* temp = (int*)malloc(n * sizeof(int));
	KnapBacktrack(0,0,0,0,temp,n,w,v,x,c);
}


//=======================================��֧�޽編====================================================================
int Bound(int i, int cw, int cv,int* w,int* v,int c, int n){
	int cleft = c - cw;
	int bound = cv;
	while (i <= n && w[i - 1] <= cleft) {
		cleft -= w[i - 1];
		bound += v[i - 1];
		i++;
	}
	//��ʱi��Ʒ��ûװ�����Ѿ�������ȫװ���ˣ����ԾͰ�������ʣ�µ�װ��
	if (i <= n) bound += v[i - 1] / w[i - 1] * cleft;
	return bound;
}

int BranchBound(int n,int* v,int* w, int c){
	int temp, tempv, tempw;
	int j;
	int* kn = (int*)malloc( n * sizeof(int));
	for (int i = 0; i < n; i++) kn[i] = v[i] / w[i];
	for (int i = 1; i <= n - 1; i++) {
		if (kn[i] <= kn[i - 1])
			continue;
		else {
			temp = kn[i];
			tempw = w[i];
			tempv = v[i];
			for (j = i - 1; j >= 0; j--) {
				if (kn[j] < temp) {
					kn[j + 1] = kn[j];
					w[j + 1] = w[j];
					v[j + 1] = v[j];
				}
				else break;
			}
			kn[j + 1] = temp;
			w[j + 1] = tempw;
			v[j + 1] = tempv;
		}
	}
	//cwΪ��ǰװ��������cvΪ��ǰװ����ֵ��bestvΪ��ǰ����ֵ
	int cw = 0;
	int cv = 0;
	int bestv = 0;
	int i = 1;
	int up = 0; //upΪ���ļ�ֵ�Ͻ磻
	priority_queue<PriorNode> q;       //�������ȶ���
	up = Bound(i,cw,cv,w,v,c,n); // i�ǵ�i��stuff
	while (i != n + 1) {
		// ���Ӽ�Ϊ��iװ�뱳�����Һ���Ϊ����iװ�뱳��
		if (cw + w[i - 1] <= c) {         //�����ǿ��н�㣬����뱳��
			if (cv + v[i - 1] > bestv) bestv = cv + v[i - 1];
			PriorNode plnode = { up,cv + v[i - 1], cw + w[i - 1], true, i + 1 };
			q.push(plnode);
		}
		up = Bound(i+1, cw,cv,w,v,c,n);
		if (up >= bestv) {//������������ܰ������Ž�
			PriorNode prnode = { up,cv , cw , false, i + 1 };
			q.push(prnode);
		}
		up = q.top().up;
		cv = q.top().cv;
		cw = q.top().cw;
		i = q.top().number;
		q.pop();
	}
	return cv;
}


//=======================================���ؿ��巨====================================================================
int MC_Packet(int* w, int* v, int* x, int c, int n)
{
	int test[100000] = { 0 };
	int value[100000] = {0};
	srand((unsigned)time(NULL));
	int max = 0;
	for (int j = 0; j <= 100000 - 1; j++) {
		for (int i = 0; i < n; i++) {
			x[i] = rand() % 2;
			test[j] += x[i] * w[i];
			value[j] += x[i] * v[i];
		}
		if (test[j] > c){
			test[j] = -1;
		}
		else
			if (value[j] > max) max = value[j];
	}
	return max;
}


int _tmain(int argc, _TCHAR* argv[])
{

	int* w;
	int* v;
	int c;	//�����ߴ�
	int n;	//��Ʒ����	
	int m[20][100] = {0};		//��̬�滮����
	int x[20] = {0};			//�����
	
	ifstream infile;
	infile.open("input.txt", ios::binary);
	cout << "Reading from the file..." << endl;
	// line1
	string data_n;
	getline(infile, data_n);
	cout << data_n << endl;
	n = atoi(data_n.c_str());
	w = (int*)malloc(n * sizeof(int));
	v = (int*)malloc(n * sizeof(int));
	// line2
	string data_c;
	getline(infile, data_c);
	cout << data_c << endl;
	c = atoi(data_c.c_str());
	// line3
	string data_w;
	getline(infile, data_w);
	cout << data_w << endl;
	getInt(data_w, w,n);
	// line4
	string data_v;
	getline(infile, data_v);
	cout << data_v << endl;
	getInt(data_v, v,n);
	cout << "����ɹ���" << endl;
	
	ofstream outfile;
	outfile.open("ouput.txt");

	//��ٷ�exhaustion
	int numerate[1024][10] = {0};
	createExhaustion(numerate, n);
	int number = (int)pow(2,double(n));
	int max,temp,index,i,j;
	max = 0;
	for(j = 0; j < number; j++){
		temp = findsolution(numerate[j], n, v, w, c);
		if(temp>max){
			max = temp; 
			index = j;
		}	
	}
	//printSolve(numerate[index],n);
	outfile << "��ٷ�:" << max << endl;

	//��̬�滮�㷨 Dynamic planning 
	Knapsack(v,w,c,n,m);
	Traceback(w,c,n,m,x);
	//printSolve(x,n);
	outfile << "��̬�滮:" << m[0][c] << endl;

	//�Զ����µı���¼�� Memo method
	Memorized(m,n,v,w,c);
	Traceback(w,c,n,m,x);
	//printSolve(x,n);
	outfile << "�Զ����µı���¼��:" << m[0][c] << endl;

	//���ݷ� Ҫ������޽纯�� recall
	BackTrack_Packet( n, w, v, x, c);
	//printSolve(x,n);
	outfile << "���ݷ�:" << m[0][c] << endl;

	//��֧�޽編 branch bounding method
 	max = BranchBound(n,v,w,c);
	outfile << "��֧�޽編" << max << endl;

	//���ؿ��巨 Monte Carlo
	//max = packet.max;
	max = MC_Packet(w,v,x,c,n);
	outfile << "���ؿ��巨:" << max << endl;

	system("pause");
	return 0;
}

