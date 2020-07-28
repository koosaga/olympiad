// Ivan Carvalho
// Solution to https://dmoj.ca/problem/tle16c1p5
#include <cstdio>
#include <vector>
#include <algorithm>
#define MAXN 100010
#define MP make_pair
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
vector<ii> grafo[MAXN];
ll arvore[4*MAXN],custo[MAXN],nivel[MAXN],distancia[MAXN],resposta[MAXN],n,vetorzao[MAXN],P[MAXN];
void update(ll pos,ll left,ll right,ll x,ll val){
	if(left == right){
		arvore[pos] = val;
		return;
	}
	ll mid = (left+right)/2;
	if(x <= mid){
		update(2*pos,left,mid,x,val);
	}
	else{
		update(2*pos+1,mid+1,right,x,val);
	}
	arvore[pos] = min(arvore[2*pos],arvore[2*pos+1]);
}
ll query(ll pos,ll left,ll right,ll i,ll j){
	if(left >= i && right<=j){
		return arvore[pos];
	}
	ll mid = (left+right)/2;
	if(j <= mid){
		return query(2*pos,left,mid,i,j);
	}
	else if(i >= mid + 1){
		return query(2*pos+1,mid+1,right,i,j);
	}
	return min(query(2*pos,left,mid,i,j),query(2*pos+1,mid+1,right,i,j));
}
void dfs(ll v,ll p){
	vetorzao[nivel[v]] = v;
	update(1,1,n,nivel[v],P[v]);
	if(nivel[v] <= 2){
		custo[v] = distancia[v]*P[v];
	}
	else{
		ll ini = 1,fim = nivel[v] - 1,resp = 1,meio;
		while(ini <= fim){
			meio = (ini+fim)/2;
			if(query(1,1,n,meio,nivel[v]-1) <= P[v]){
				resp = meio;
				ini = meio + 1;
			}
			else{
				fim = meio - 1;
			}
		}
		custo[v] = custo[vetorzao[resp]] + (distancia[v] - distancia[vetorzao[resp]])*P[v];
	}
	for(ll i=0;i<grafo[v].size();i++){
		ll u = grafo[v][i].first;
		ll peso = grafo[v][i].second;
		if(u == p) continue;
		nivel[u] = nivel[v] + 1;
		distancia[u] = distancia[v] + peso;
		dfs(u,v);
	}
}
int main(){
	scanf("%lld",&n);
	for(ll i=1;i<n;i++){
		ll c,d,p;
		scanf("%lld %lld %lld",&p,&d,&c);
		P[i] = c;
		grafo[p].push_back(MP(i,d));
		grafo[i].push_back(MP(p,d));
	}
	nivel[n] = 1;
	dfs(n,-1);
	for(ll i=1;i<n;i++) printf("%lld\n",custo[i]);
	return 0;
}	return 0;
}