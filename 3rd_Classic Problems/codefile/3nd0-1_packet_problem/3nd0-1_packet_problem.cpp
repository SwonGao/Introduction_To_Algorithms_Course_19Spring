// 3nd0-1_packet_problem.cpp : 定义控制台应用程序的入口点。

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
	//注：重载>号会编译出错，因为标准库默认使用元素类型的<操作符来确定它们之间的优先级关系。
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

// 将解打印出来
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

//=======================================枚举法====================================================================

//创建枚举数组
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


//=======================================动态规划====================================================================
// 动态规划
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
	}//暂时对i=0 不作处理
	if(c>=w[0])
		m[0][c] = (int)max(m[1][c],m[1][c-w[0]]+v[0]);
	else
		m[0][c] = m[1][c];
	//return m;
}

// 动态规划Traceback
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


//=======================================自顶向下的备忘录法====================================================================

int Lookup(int i, int j, int m[][100],int n, int* v, int* w, int c){
	int jMax;
	if(i<0 || j<0) return -1;
	if(m[i][j]>0 ) return m[i][j];
	//如果查到，返回	如果没查到：创造这个值。
	if(i == n-1){
		jMax = (int)min(w[n-1]-1,c);
		if( j <= jMax)	m[n-1][j] = 0;
		else			m[n-1][j] = v[n-1];			
		return m[n-1][j];
	}// 创建初始条件
	else if(i == 0){
		if(c>=w[0])
			m[0][c] = (int)max( (double)Lookup(1,c,m,n,v,w,c) , (double)Lookup(1,c-w[0],m,n,v,w,c) + v[0]);
		else
			m[0][c] = Lookup(1,c,m,n,v,w,c);
		return m[0][c];
	}// 分开处理
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
	// 查询m[0][c]
	return Lookup(0, c, m,n,v,w,c);
}


//=======================================回溯法====================================================================

int KnapBacktrack(int i, int cw,int cv, int bestv, int* temp, int n, int* w,int* v, int* x,int c)
{
	if (i > n-1) {
		if (bestv < cv) {
			bestv = cv;
			for (int j = 0; j < n; x[j] = temp[j++]);
		}
		return bestv;
	}// 搜索到可行解
	else {
		if (cw + w[i] <= c) {
			int sum = 0;
			for (int t = i; t <= n - 1; sum += v[t++]); //限界
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
		for (int t = i + 1; t <= n - 1; sum += v[t++]); //限界
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


//=======================================分支限界法====================================================================
int Bound(int i, int cw, int cv,int* w,int* v,int c, int n){
	int cleft = c - cw;
	int bound = cv;
	while (i <= n && w[i - 1] <= cleft) {
		cleft -= w[i - 1];
		bound += v[i - 1];
		i++;
	}
	//此时i物品还没装但是已经不能完全装下了，所以就按比例把剩下的装下
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
	//cw为当前装包重量，cv为当前装包价值，bestv为当前最优值
	int cw = 0;
	int cv = 0;
	int bestv = 0;
	int i = 1;
	int up = 0; //up为结点的价值上界；
	priority_queue<PriorNode> q;       //定义优先队列
	up = Bound(i,cw,cv,w,v,c,n); // i是第i个stuff
	while (i != n + 1) {
		// 左孩子即为将i装入背包，右孩子为不将i装入背包
		if (cw + w[i - 1] <= c) {         //左孩子是可行结点，则加入背包
			if (cv + v[i - 1] > bestv) bestv = cv + v[i - 1];
			PriorNode plnode = { up,cv + v[i - 1], cw + w[i - 1], true, i + 1 };
			q.push(plnode);
		}
		up = Bound(i+1, cw,cv,w,v,c,n);
		if (up >= bestv) {//如果右子树可能包含最优解
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


//=======================================蒙特卡洛法====================================================================
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
	int c;	//背包尺寸
	int n;	//物品总量	
	int m[20][100] = {0};		//动态规划矩阵
	int x[20] = {0};			//输出解
	
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
	cout << "读入成功！" << endl;
	
	ofstream outfile;
	outfile.open("ouput.txt");

	//穷举法exhaustion
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
	outfile << "穷举法:" << max << endl;

	//动态规划算法 Dynamic planning 
	Knapsack(v,w,c,n,m);
	Traceback(w,c,n,m,x);
	//printSolve(x,n);
	outfile << "动态规划:" << m[0][c] << endl;

	//自顶向下的备忘录法 Memo method
	Memorized(m,n,v,w,c);
	Traceback(w,c,n,m,x);
	//printSolve(x,n);
	outfile << "自顶向下的备忘录法:" << m[0][c] << endl;

	//回溯法 要求包含限界函数 recall
	BackTrack_Packet( n, w, v, x, c);
	//printSolve(x,n);
	outfile << "回溯法:" << m[0][c] << endl;

	//分支限界法 branch bounding method
 	max = BranchBound(n,v,w,c);
	outfile << "分支限界法" << max << endl;

	//蒙特卡洛法 Monte Carlo
	//max = packet.max;
	max = MC_Packet(w,v,x,c,n);
	outfile << "蒙特卡洛法:" << max << endl;

	system("pause");
	return 0;
}

