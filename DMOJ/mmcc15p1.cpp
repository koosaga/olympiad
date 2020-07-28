// Ivan Carvalho
// Solution to https://dmoj.ca/problem/mmcc15p1
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 10;
int pai[MAXN],tamanho[MAXN],oldtam1[MAXN],oldtam2[MAXN],oldpai1[MAXN],oldpai2[MAXN],ponteiro,n;

int find(int x){
	if(x == pai[x]) return x;
	return find(pai[x]);
}

void AddEdge(int x,int y){
	x = find(x);
	y = find(y);
	if(x == y){
		ponteiro++;
		oldtam1[ponteiro] = oldtam2[ponteiro] = tamanho[x];
		oldpai1[ponteiro] = oldpai2[ponteiro] =  x;
		return;
	}
	if(tamanho[x] < tamanho[y]) swap(x,y);
	ponteiro++;
	oldpai1[ponteiro] = x;
	oldpai2[ponteiro] = y;
	oldtam1[ponteiro] = tamanho[x];
	oldtam2[ponteiro] = tamanho[y];
	pai[y] = x;
	tamanho[x] =  tamanho[x] + tamanho[y];
}

void Init(int N){
	n = N;
	for(int i = 1;i<=n;i++){
		pai[i] = i;
		tamanho[i] = 1;
	}
}

void RemoveLastEdge(){
	pai[oldpai1[ponteiro]] = oldpai1[ponteiro];
	pai[oldpai2[ponteiro]] = oldpai2[ponteiro];
	tamanho[oldpai1[ponteiro]] = oldtam1[ponteiro];
	tamanho[oldpai2[ponteiro]] = oldtam2[ponteiro];
	ponteiro--;
}

int GetSize(int U){
	return tamanho[find(U)];
}

int main(){
	return 0;
}
