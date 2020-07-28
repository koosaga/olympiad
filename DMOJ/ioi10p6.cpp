// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi10p6
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll MAXN = 1e6 + 10;
vector<ll> grafo[MAXN];
ll tam[MAXN],soma,maior[MAXN],n,num[MAXN],resp,vertice,total;
void dfs(ll v,ll p){
	tam[v] = num[v];
	for(ll u : grafo[v]){
		if(u != p){
			dfs(u,v);
			tam[v] += tam[u];
			maior[v] = max(maior[v],tam[u]);
		}
	}
	maior[v] = max(maior[v],total - tam[v]);
}
int LocateCentre(int N,int P[],int S[],int D[]){
	n = N;
	for(ll i=0;i<n;i++){
		num[i] = P[i];
		total += num[i];
	}
	for(ll i=0;i+1<n;i++){
		ll u,v;
		u = S[i];
		v = D[i];
		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}
	dfs(0,-1);
	resp = maior[0];
	for(ll i=1;i<n;i++){
		if(maior[i] < resp){
			resp = maior[i];
			vertice = i;
		}
	}
	return (int)vertice;
}

int main(){
    return 0;
}
