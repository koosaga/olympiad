// Ivan Carvalho
// Solution to https://dmoj.ca/problem/si17c3p5
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
const int MAXN = (int)1e5 + 10;
long long resposta;
vector<ii> grafo[MAXN];
int tam[MAXN],ac[MAXN],n;
map<int,int> *cjt[MAXN];
void dfs(int v,int p){
	tam[v] = 1;
	int mx = -1,big = -1,ligabig = 0;
	for(int i = 0;i<grafo[v].size();i++){
		int u = grafo[v][i].first, w = grafo[v][i].second;
		if(u == p) continue;
		dfs(u,v);
		tam[v] += tam[u];
		if(tam[u] >= mx){
			mx = tam[u];
			big = u;
			ligabig = w;
		}
	}
	if(big == -1){
		cjt[v] = new map<int,int>();
		(*cjt[v])[0] = 1;
	}
	else{
		cjt[v] = cjt[big];
		ac[v] = ac[big] + ligabig;
		if(cjt[v]->count(-1 - ac[v])) resposta += 1LL*(*cjt[v])[-1 - ac[v]];
		if(cjt[v]->count(1 - ac[v])) resposta += 1LL*(*cjt[v])[1 - ac[v]];
		(*cjt[v])[-ac[v]]++;
	}
	for(int i = 0;i<grafo[v].size();i++){
		int u = grafo[v][i].first, w = grafo[v][i].second;
		if(u == p || u == big) continue;
		for(map<int,int>::iterator it = cjt[u]->begin();it != cjt[u]->end();it++){
			int x = (*it).first + ac[u] + w, qtd = (*it).second;
			if(cjt[v]->count(-x - 1 - ac[v])) resposta += 1LL*qtd*(*cjt[v])[-x - 1 - ac[v]];
			if(cjt[v]->count(-x + 1 - ac[v])) resposta += 1LL*qtd*(*cjt[v])[-x + 1 - ac[v]];
		}
		for(map<int,int>::iterator it = cjt[u]->begin();it != cjt[u]->end();it++){
			int x = (*it).first + ac[u] + w, qtd = (*it).second;
			(*cjt[v])[x - ac[v]] += qtd;
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i = 1;i<n;i++){
		int u,v;
		char c;
		scanf("%d %d %c",&u,&v,&c);
		int w = (c == 'r') ? (1) : (-1);
		grafo[v].push_back(ii(u,w));
		grafo[u].push_back(ii(v,w));
	}
	dfs(1,-1);
	printf("%lld\n",resposta - 1LL*(n - 1));
	return 0;
}