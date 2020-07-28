// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc03s5
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
const int BUCKET_SIZE = 101;
const int MAXN = BUCKET_SIZE*BUCKET_SIZE;
vector<iii> Kruskal;
vector<ii> grafo[MAXN];
int parent[MAXN],pai[MAXN],superpai[MAXN],ligapai[MAXN],ligasuperpai[MAXN],nivel[MAXN];
int find(int x){
	if(x == parent[x]) return x;
	return parent[x] = find(parent[x]);
}
void join(int x,int y){
	x = find(x);
	y = find(y);
	if(x == y) return;
	if(rand() % 2 == 1) swap(x,y);
	parent[x] = y;
}
void dfs_pai(int x){
	for(int i=0;i<grafo[x].size();i++){
		int v = grafo[x][i].first, peso = grafo[x][i].second;
		if(pai[v] == 0){
			pai[v] = x;
			nivel[v] = nivel[x] + 1;
			ligapai[v] = peso;
			dfs_pai(v);
		}
	}
}
void dfs_superpai(int x,int p){
	superpai[x] = p;
	if(nivel[x] % BUCKET_SIZE == 0){
		p = x;
	}
	for(int i=0;i<grafo[x].size();i++){
		int v = grafo[x][i].first;
		if(superpai[v] == 0){
			dfs_superpai(v,p);
		}
	}
}
int LCA(int u,int v){
	int resp = 1e9;
	while(superpai[u] != superpai[v]){
		if(nivel[u] < nivel[v]) swap(u,v);
		resp = min(resp,ligasuperpai[u]);
		u = superpai[u];
	}
	while(u != v){
		if(nivel[u] < nivel[v]) swap(u,v);
		resp = min(resp,ligapai[u]);
		u = pai[u];
	}
	return resp;
}
int main(){
	int n,m,d;
	int resp = 1e9;
	scanf("%d %d %d",&n,&m,&d);
	for(int i=1;i<=n;i++) parent[i] = i;
	for(int i=0;i<m;i++){
		int u,v,peso;
		scanf("%d %d %d",&u,&v,&peso);
		Kruskal.push_back(MP(peso,MP(u,v)));
	}
	sort(Kruskal.begin(),Kruskal.end());
	for(int i = m-1;i>=0;i--){
		if(find(Kruskal[i].second.first) != find(Kruskal[i].second.second)){
			join(Kruskal[i].second.first,Kruskal[i].second.second);
			grafo[Kruskal[i].second.first].push_back(MP(Kruskal[i].second.second,Kruskal[i].first));
			grafo[Kruskal[i].second.second].push_back(MP(Kruskal[i].second.first,Kruskal[i].first));
		}
	}
	pai[1] = 1;
	dfs_pai(1);
	dfs_superpai(1,1);
	for(int i=1;i<=n;i++){
		int temp = i;
		int maior = 1e9;
		int alvo = superpai[i];
		while(temp != alvo){
			maior = min(maior,ligapai[temp]);
			temp = pai[temp];
		}
		ligasuperpai[i] = maior;
	}
	for(int i=1;i<=d;i++){
		int v;
		scanf("%d",&v);
		resp = min(resp,LCA(1,v));
	}
	printf("%d\n",resp);
	return 0;
}printf("%d\n",resp);
	return 0;
}