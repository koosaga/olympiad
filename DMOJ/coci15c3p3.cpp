// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci15c3p3
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;

vector<int> grafo[MAXN];
int e1[MAXN],e2[MAXN],e3[MAXN],e4[MAXN],N;

void dfs(int v,int cor,int p){

	for(int i : grafo[v]){
		int u = (e1[i] != v) ? (e1[i]) : (e2[i]);
		if(u == p) continue;
		if(cor){
			e3[i] = v;
			e4[i] = u;
		}
		else{
			e3[i] = u;
			e4[i] = v;
		}
		dfs(u,cor ^ 1,v);
	}

}

int main(){

	scanf("%d",&N);
	for(int i = 1;i<N;i++){
		scanf("%d %d",&e1[i],&e2[i]);
		grafo[e1[i]].push_back(i);
		grafo[e2[i]].push_back(i);
	}

	dfs(1,0,-1);
	for(int i = 1;i<N;i++){
		if(e1[i] == e3[i]) printf("1\n");
		else printf("0\n");
	}

	return 0;
}