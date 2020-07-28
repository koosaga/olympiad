// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci15c4p4
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N,K,Q;
ll get_pow(ll pot){
	ll resp = 1;
	for(ll i=1;i<=pot;i++) resp *= K;
	return resp;
}
ll get_level(ll x){
	ll pot = 1,nivel = 0;
	while(x > 0){
		//printf("%lld\n",x);
		x -= pot;
		pot *= K;
		nivel++;
	}
	return nivel;
}
ll get_first_level(ll nivel){
	if(nivel == 0) return 1;
	ll ac = 0;
	ll pot = 1;
	for(ll i = 1;i <nivel;i++){
		ac += pot;
		pot *= K;
	}
	return ac + 1;
}
ll get_parent(ll x){
	if(x == 1) return 1;
	ll nivel = get_level(x);
	ll primeiro = get_first_level(nivel - 1);
	ll ultimo = get_first_level(nivel) - 1;
	ll ini = primeiro, fim = ultimo,meio;
	while(ini <= fim){
		meio = (ini + fim)/2;
		ll delta = meio - primeiro;
		ll esimo1 = ultimo + 1 + delta*K;
		ll esimok = esimo1 + K - 1;
		if(esimo1 <= x && x <= esimok){
			return meio;
		}
		if(x < esimo1){
			fim = meio - 1;
		}
		else ini = meio + 1;
	}
}
ll LCA(ll u, ll v){
	while(u != v){
		if(get_level(u ) < get_level(v)) swap(u,v);
		//printf("U %lld P %lld\n",u,get_parent(u));
		u = get_parent(u);
	}
	return u;
}
int main(){
	scanf("%lld %lld %lld",&N,&K,&Q);
	while(Q--){
		ll u,v;
		scanf("%lld %lld",&u,&v);
		printf("%lld\n",get_level(u) + get_level(v) - 2*get_level(LCA(u,v)));
	}
	return 0;
}