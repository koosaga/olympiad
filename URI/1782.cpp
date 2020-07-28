// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1782
#include <cstdio>
#include <vector>
#include <algorithm>
#define MAXN 100010
#define MP make_pair
using namespace std;
typedef long long ll;
#define gc getchar_unlocked
void getint(ll &x){
    register ll c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
typedef pair<ll,ll> ii;
typedef pair<ll,ii> iii;
ll pai[MAXN],qtd[MAXN],formas,respostas[MAXN],minhasformas[MAXN],n,q;
vector<ii> queries;
vector<iii> arestas;
ll find(ll x){
	if(x == pai[x]) return x;
	return pai[x] = find(pai[x]);
}
void join(ll x, ll y){
	x = find(x);
	y = find(y);
	if(x == y) return;
	if(qtd[x] < qtd[y]) swap(x,y);
	formas -= minhasformas[x];
	formas -= minhasformas[y];
	qtd[x] += qtd[y];
	minhasformas[x] = qtd[x] + (qtd[x]*(qtd[x]-1))/2;
	formas += minhasformas[x];
	pai[y] = x;
}
int main(){
	ll TC;
	getint(TC);
	for(ll tc=1;tc<=TC;tc++){
		queries.clear();
		arestas.clear();
		printf("Caso #%lld:",tc);
		formas = 0;
		scanf("%lld",&n);
		for(ll i=1;i<=n;i++){
			formas++;
			minhasformas[i] = 1;
			qtd[i] = 1;
			pai[i] = i;
		}
		for(ll i=1;i<n;i++){
			ll u,v,peso;
			getint(u);
			getint(v);
			getint(peso);
			arestas.push_back(MP(peso,MP(u,v)));
		}
		getint(q);
		for(ll i=1;i<=q;i++){
			ll peso;
			getint(peso);
			queries.push_back(MP(peso,i));
		}
		sort(queries.begin(),queries.end());
		sort(arestas.begin(),arestas.end());
		ll idx = 0;
		for(ll i=0;i<q;i++){
			while(idx < n - 1 && arestas[idx].first <= queries[i].first){
				join(arestas[idx].second.first,arestas[idx].second.second);
				idx++;
			}
			respostas[queries[i].second] = formas;
		}
		for(ll i=1;i<=q;i++){
			printf(" %lld",respostas[i]);
		}
		printf("\n");
	}
	return 0;
}
