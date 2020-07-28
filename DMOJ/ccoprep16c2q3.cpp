// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccoprep16c2q3
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
#define MAXN 200010
#define gc getchar_unlocked
inline void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
inline void print(int n){		
	char buf[11];
	buf[10] = '\n';
	int i = 9;
	while (n){
		buf[i--] = n % 10 + '0';
		n /= 10;
	}
	while (buf[i] != '\n') putchar_unlocked(buf[++i]);
}
using namespace std;
vector<int> grafo[MAXN],especiais;
int K[MAXN],pai[MAXN],custo[MAXN],marcado[MAXN],n,q,sqn;
int e1[MAXN],e2[MAXN],e3[MAXN];
void dfs(int v,int sp){
	pai[v] = sp;
	for(int u : grafo[v]){
		if(marcado[u]) continue;
		custo[u] = custo[v] + 1;
		dfs(u,sp);
	}
}
void build_graph(){
	for(int i=0;i<=n;i++){
		grafo[i].clear();
	}
	for(int i=0;i<n;i++){
		int prox = min(i + K[i],n);
		grafo[prox].push_back(i);
		custo[i] = 0;
	}
	for(int v : especiais){
		dfs(v,v);
	}
	dfs(n,n);
	for(int v : especiais){
		int prox = min(v + K[v],n);
		pai[v] = prox;
		custo[v] = 1;
	}
}
int doQuery(int v){
	int resp = 0;
	while(v != n){
		//printf("Q : %d %d %d\n",v,custo[v],pai[v]);
		resp += custo[v];
		v = pai[v];
	}
	return resp;
}
int main(){
	getint(n);
	for(int i=0;i<n;i++) getint(K[i]);
	getint(q);
	sqn = sqrt(2*n);
	for(int i=0;i<q;i++){
		getint(e1[i]);
		getint(e2[i]);
		if(e1[i] == 2) getint(e3[i]);
	}
	int ini = 0, fim = sqn - 1;
	while(ini < q){
		fim = min(q-1,fim);
		//printf("Block %d %d\n",ini,fim);
		for(int v : especiais){
			marcado[v] = 0;
		}
		especiais.clear();
		for(int i = ini;i<=fim;i++){
			if(e1[i] == 2 && !marcado[e2[i]]){
				marcado[e2[i]] = 1;
				especiais.push_back(e2[i]);
			}
		}
		build_graph();
		for(int i = ini;i<=fim;i++){
			int op = e1[i];
			if(op == 1){
				print(doQuery(e2[i]));
			}
			else{
				int v = e2[i],k = e3[i];
				K[v] = k;
				int prox = min(v + k,n);
				pai[v] = prox;
			}
		}
		ini += sqn;
		fim += sqn;
	}
	return 0;
}
		fim += sqn;
	}
	return 0;
}