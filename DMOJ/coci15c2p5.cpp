// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci15c2p5
#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))
using namespace std;
typedef long long ll;
const ll MAXN = 1000010;
ll bit[MAXN],vetor[MAXN];
void update(ll pos){
	while(pos < MAXN){
		bit[pos]++;
		pos += LSOne(pos);
	}
}
ll read(ll pos){
	ll ans = 0;
	while(pos > 0){
		ans += bit[pos];
		pos -= LSOne(pos);
	}
	return ans;
}
vector<ll> comp;
int main(){
	ll n;
	scanf("%lld",&n);
	comp.push_back(0);
	for(ll i=1;i<=n;i++) scanf("%lld",&vetor[i]);
	ll p;
	scanf("%lld",&p);
	ll soma = 0,resp = 0;
	for(ll i=1;i<=n;i++){
		soma += vetor[i];
		soma -= p;
		comp.push_back(soma);
	}
	sort(comp.begin(),comp.end());
	comp.erase(unique(comp.begin(),comp.end()),comp.end());
	soma = 0;
	for(ll i=0;i<=n;i++){
		soma += vetor[i];
		if(i)soma -= p;
		ll davez = lower_bound(comp.begin(),comp.end(),soma) - comp.begin() + 1;
		resp += read(davez);
		update(davez);
	}
	printf("%lld\n",resp);
	return 0;
}