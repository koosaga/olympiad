// Ivan Carvalho
// Solution to https://www.spoj.com/problems/QTREE2/
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#define MAXN 10010
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
vector<ii> grafo[MAXN];
int pai[MAXN],superpai[MAXN],nivel[MAXN],dist[MAXN],segmento,TC,n;
void dfs_pai(int x){
	for(int i=0;i<grafo[x].size();i++){
		int v = grafo[x][i].first, peso = grafo[x][i].second;
		if(!pai[v]){
			pai[v] = x;
			nivel[v] = nivel[x] + 1;
			dist[v] = dist[x] + peso;
			dfs_pai(v);
		}
	}
}
void dfs_superpai(int x,int p){
	superpai[x] = p;
	if(nivel[x] % segmento == 0){
		p = x;
	}
	for(int i=0;i<grafo[x].size();i++){
		int v = grafo[x][i].first;
		if(!superpai[v]){
			dfs_superpai(v,p);
		}
	}
}
int LCA(int u,int v){
	while(superpai[u] != superpai[v]){
		if(nivel[u] > nivel[v]){
			u = superpai[u];
		}
		else{
			v = superpai[v];
		}
	}
	while(u != v){
		if(nivel[u] > nivel[v]){
			u = pai[u];
		}
		else{
			v = pai[v];
		}
	}
	return u;
}
int KTH(int u,int v,int k){
	int ancestor = LCA(u,v);
	int distu = nivel[u] - nivel[ancestor];
	int distv = nivel[v] - nivel[ancestor];
	if(k == 1) return u;
	if(k == distu + distv + 1) return v;
	k--;
	if(distu >= k){
		int targeth = nivel[u] - k;
		//printf("T %d U %d\n",targeth,u);
		while(nivel[u] != targeth){
			if(nivel[superpai[u]] >= targeth){
				u = superpai[u];
			}
			else u = pai[u];
			//printf("Novo U %d\n",u);
		}
		return u;
	}
	else{
		k = k - distu;
		int targeth = nivel[ancestor] + k;
		//printf("T %d V %d\n",targeth,v);
		while(nivel[v] != targeth){
			if(nivel[superpai[v]] >= targeth){
				v = superpai[v];
			}
			else v = pai[v];
			//printf("Novo V %d\n",v);
		}
		return v;
	}
}
int main(){
	scanf("%d",&TC);
	while(TC--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			grafo[i].clear();
			pai[i] = 0;
			superpai[i] = 0;
			dist[i] = 0;
			nivel[i] = 0;
		}
		for(int i=1;i<n;i++){
			int u,v,peso;
			scanf("%d %d %d",&u,&v,&peso);
			grafo[u].push_back(MP(v,peso));
			grafo[v].push_back(MP(u,peso));
		}
		pai[1] = 1;
		nivel[1] = 0;
		dist[1] = 0;
		dfs_pai(1);
		int maioraltura = 0;
		for(int i=1;i<=n;i++){
			maioraltura = max(maioraltura,nivel[i]);
		}
		segmento = sqrt(maioraltura);
		dfs_superpai(1,1);
		char entrada[20];
		while(true){
			scanf("%s",entrada);
			if(entrada[1] == 'O') break;
			if(entrada[0] == 'D'){
				int u,v;
				scanf("%d %d",&u,&v);
				int ancestor = LCA(u,v);
				int distu = dist[u] - dist[ancestor];
				int distv = dist[v] - dist[ancestor];
				printf("%d\n",distu+distv);
			}
			else if(entrada[0] == 'K'){
				int u,v,k;
				scanf("%d %d %d",&u,&v,&k);
				printf("%d\n",KTH(u,v,k));
			}
		}
	}
	return 0;
}