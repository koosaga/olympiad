// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi11p2
#include <bits/stdc++.h>
#define MP make_pair
#define PB push_back
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef map<ll,ll>::iterator ite;
ll N,K,resp;
const ll MAXN = 200010;
vector<ii> grafo[MAXN];
map<ll,ll> *conjunto[MAXN];
ll tam[MAXN],percorrido[MAXN],nivel[MAXN],ac1[MAXN],ac2[MAXN];
void dfs_sack(ll v,ll p){
	tam[v] = 1;
	ll big = -1,ligabig = -1,mx = -1;
	for(ll i=0;i<grafo[v].size();i++){
		ll u = grafo[v][i].first, ligau = grafo[v][i].second;
		if(u != p){
			nivel[u] = nivel[v] + 1;
			percorrido[u] = percorrido[v] + ligau;
			dfs_sack(u,v);
			tam[v] += tam[u];
			if(tam[u] > mx){
				mx = tam[u];
				ligabig = ligau;
				big = u;
			}
		}
	}
	if(big == -1){
		conjunto[v] = new map<ll,ll> ();
		(*conjunto[v])[0] = 0;
	}
	else{
		conjunto[v] = conjunto[big];
		ac1[v] = ac1[big] + ligabig;
		ac2[v] = ac2[big] + 1;
		if((*conjunto[v]).count(K - ac1[v])) resp = min(resp,(*conjunto[v])[K - ac1[v]] + ac2[v]);
		(*conjunto[v])[-ac1[v]] = -ac2[v];
	}
	for(ll i=0;i<grafo[v].size();i++){
		ll u = grafo[v][i].first, ligau = grafo[v][i].second;
		if(u != p && u != big){
			for(ite it = (*conjunto[u]).begin();it != (*conjunto[u]).end();it++){
				ll dist1 = (*it).first + ligau + ac1[u];
				ll dist2 = (*it).second + 1 + ac2[u];
				if((*conjunto[v]).count(K - dist1 - ac1[v])) resp = min(resp,(*conjunto[v])[K- dist1 - ac1[v]] + dist2 + ac2[v]);
			}
			for(ite it = (*conjunto[u]).begin();it != (*conjunto[u]).end();it++){
				ll dist1 = (*it).first + ligau + ac1[u];
				ll dist2 = (*it).second + 1 + ac2[u];
				if((*conjunto[v]).count(dist1 - ac1[v])){
					(*conjunto[v])[dist1 - ac1[v]] = min((*conjunto[v])[dist1 - ac1[v]],dist2 - ac2[v]);
				}
				else{
					(*conjunto[v])[dist1 - ac1[v]] = dist2 - ac2[v];
				}
			}
		}
	}
}
int best_path(int n, int k, int h[][2], int l[]){
	resp = MAXN;
	N = n;
	K = k;
	for(int i = 0;i<n-1;i++){
		ll u = h[i][0];
		ll v = h[i][1];
		ll peso = l[i]; 
		u++;
		v++;
		grafo[u].PB(MP(v,peso));
		grafo[v].PB(MP(u,peso));
	}
	dfs_sack(1,-1);
	if(resp == MAXN) resp = -1;
	return resp;
}
int main(){
	return 0;
}
