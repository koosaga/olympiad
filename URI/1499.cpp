// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1499
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
#define MP make_pair
typedef long long ll;
typedef pair<ll,ll> ii;
const int MAXN = 4*(1e4 + 1);
int N,Q;
vector<int> nlogonia[MAXN],quadradonia[MAXN];
int maior_quadradonia[MAXN],maior_nlogonia[MAXN],aux_nlogonia,aux_quadradonia,processado[MAXN],diametro_nlogonia,diametro_quadradonia;
ll soma[MAXN],acumulada[MAXN],diametro;
void dfs_nlogonia(int x,int dist){
	processado[x] = 1;
	if(dist > diametro_nlogonia){
		diametro_nlogonia = dist;
		aux_nlogonia = x;
	}
	maior_nlogonia[x] = max(maior_nlogonia[x],dist);
	for(int i=0;i<nlogonia[x].size();i++){
		int v = nlogonia[x][i];
		if(!processado[v]) dfs_nlogonia(v,dist+1);
	}
}
void dfs_quadradonia(int x,int dist){
	processado[x] = 1;
	if(dist > diametro_quadradonia){
		diametro_quadradonia = dist;
		aux_quadradonia = x;
	}
	maior_quadradonia[x] = max(maior_quadradonia[x],dist);
	for(int i=0;i<quadradonia[x].size();i++){
		int v = quadradonia[x][i];
		if(!processado[v]) dfs_quadradonia(v,dist+1);
	}
}
int main(){
	while(scanf("%d %d",&N,&Q) != EOF){
		for(int i=0;i<=max(N,Q);i++){
			nlogonia[i].clear();
			quadradonia[i].clear();
			soma[i] = 0;
			acumulada[i] = 0;
			maior_nlogonia[i] = 0;
			maior_quadradonia[i] = 0;
		}
		aux_quadradonia = 0;
		aux_nlogonia = 0;
		diametro_nlogonia = 0;
		diametro_quadradonia = 0;
		diametro = 0;
		for(int i=1;i<N;i++){
			int u,v;
			getint(u);
			getint(v);
			nlogonia[u].push_back(v);
			nlogonia[v].push_back(u);
		}
		for(int i=1;i<Q;i++){
			int u,v;
			getint(u);
			getint(v);
			quadradonia[u].push_back(v);
			quadradonia[v].push_back(u);
		}
		memset(processado,0,sizeof(processado));
		dfs_nlogonia(1,0);
		memset(processado,0,sizeof(processado));
		dfs_nlogonia(aux_nlogonia,0);
		memset(processado,0,sizeof(processado));
		dfs_nlogonia(aux_nlogonia,0);
		memset(processado,0,sizeof(processado));
		dfs_quadradonia(1,0);
		memset(processado,0,sizeof(processado));
		dfs_quadradonia(aux_quadradonia,0);
		memset(processado,0,sizeof(processado));
		dfs_quadradonia(aux_quadradonia,0);
		diametro = max(diametro_quadradonia,diametro_nlogonia);
		ll resp = 0;
		for(int i=1;i<=Q;i++){
			soma[maior_quadradonia[i]]++;
		}
		for(ll i=1;i<=N;i++){
			acumulada[maior_nlogonia[i]]++;
		}
		vector<ii> conjunto_nlogonia, conjunto_quadradonia;
		for(ll i=0;i<=Q;i++){
			if(soma[i] == 0) continue;
			conjunto_quadradonia.push_back(MP(i,soma[i]));
		}
		for(ll i=0;i<=N;i++){
			if(acumulada[i] == 0) continue;
			conjunto_nlogonia.push_back(MP(i,acumulada[i]));
		}
		for(vector<ii>::iterator it1 = conjunto_quadradonia.begin();it1 != conjunto_quadradonia.end();it1++){
			for(vector<ii>::iterator it2= conjunto_nlogonia.begin();it2 != conjunto_nlogonia.end();it2++){
				resp += max((*it1).first + (*it2).first + 1,(ll)diametro)*((*it1).second * (*it2).second);
			}
		}
		ll embaixo = (ll)N * (ll)Q;
		printf("%.3lf\n",(double)resp / (double) embaixo);
	}
	return 0;
}
