// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1302
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stack>
#define MAXN 100010
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
vector<int> grafo[MAXN];
int vaipara[MAXN],n,q,pai[MAXN],paisubarvore[MAXN],ancestral[MAXN],superancestral[MAXN],nivel[MAXN],tamanho[MAXN],valor[MAXN],segmento;
int find(int x){
	if(x == pai[x]) return x;
	return pai[x] = find(pai[x]);
}
void join(int x,int y){
	x = find(x);
	y = find(y);
	if(x > y) swap(x,y);
	pai[y] = x;
}
void dfs_ancestral(int x){
	for(int i=0;i<grafo[x].size();i++){
		int v = grafo[x][i];
		if(!ancestral[v] && tamanho[v] == 0){
			ancestral[v] = x;
			paisubarvore[v] = paisubarvore[x];
			nivel[v] = nivel[x] + 1;
			dfs_ancestral(v);
		}
	}
}
void dfs_superancestral(int x,int p){
	superancestral[x] = p;
	if(nivel[x] % segmento == 0){
		p = x;
	}
	for(int i=0;i<grafo[x].size();i++){
		int v = grafo[x][i];
		if(!superancestral[v] && tamanho[v] == 0){
			dfs_superancestral(v,p);
		}
	}
}
int LCA(int u,int v){
	while(superancestral[u] != superancestral[v]){
		if(nivel[u] > nivel[v]) u = superancestral[u];
		else v = superancestral[v];
	}
	while(u != v){
		if(nivel[u] > nivel[v]) u = ancestral[u];
		else v = ancestral[v];
	}
	return u;
}
int main(){
	while(scanf("%d",&n) != EOF){
		for(int i=1;i<=n;i++){
			getint(vaipara[i]);
			grafo[i].clear();
			pai[i] = i;
			ancestral[i] = 0;
			superancestral[i] = 0;
			nivel[i] = 0;
			valor[i] = 0;
			tamanho[i] = 0;
		}
		for(int i=1;i<=n;i++){
			grafo[i].push_back(vaipara[i]);
			grafo[vaipara[i]].push_back(i);
			if(find(i) == find(vaipara[i])){
				int tamanhodociclo = 0;
				stack<int> pilha;
				int j = i;
				while(true){
					valor[j] = ++tamanhodociclo;
					//printf("J %d V[j] %d\n",j,valor[j]);
					pilha.push(j);
					j = vaipara[j];
					if(j == i) break;
				}
				while(!pilha.empty()){
					tamanho[pilha.top()] = tamanhodociclo;
					pilha.pop();
				}
			}
			join(i,vaipara[i]);
		}
		for(int i=1;i<=n;i++){
			if(tamanho[i] != 0){
				paisubarvore[i] = i;
				ancestral[i] = i;
				dfs_ancestral(i);
			}
		}
		int maior = 0;
		for(int i=1;i<=n;i++){
			maior = max(maior, nivel[i] );
		}
		segmento = sqrt(maior);
		for(int i=1;i<=n;i++){
			if(tamanho[i] != 0){
				dfs_superancestral(i,i);
			}
		}
		getint(q);
		while(q--){
			int u,v;
			getint(u);
			getint(v);
			if(find(u) != find(v)){
				printf("-1\n");
				continue;
			}
			if(paisubarvore[u] == paisubarvore[v]){
				printf("%d\n",nivel[u] + nivel[v] - 2*nivel[LCA(u,v)]);
			}
			else{
				int delta = abs(valor[paisubarvore[u]] - valor[paisubarvore[v]]);
				int mod = min(tamanho[paisubarvore[u]] - delta,delta);
				printf("%d\n",nivel[u] + nivel[v] + mod);
			}
		}
	}
	return 0;
}
