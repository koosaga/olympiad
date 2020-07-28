// Ivan Carvalho
// Solution to https://www.spoj.com/problems/BDOI16B/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll reduce(ll x,ll y){
	return x - (x % y);
}
ll count(ll x,ll y){
	ll ans = 0;
	for(ll pot = y;pot<=x;pot*=y){
		ll lo = 1;
		ll hi = reduce(x,pot)/pot;
		ans += hi - lo + 1;
	}
	return ans;
}
int main(){
	ll TC;
	cin >> TC;
	for(ll tc = 1;tc<=TC;tc++){
		map<ll,ll> mapa;
		ll n,k;
		cin >> n >> k;
		ll copia = k;
		for(ll i = 2;i*i<=k;i++){
			if(copia % i == 0){
				while(copia % i == 0){
					mapa[i]++;
					copia /= i;
				}
			}
		}
		if(copia != 1) mapa[copia]++;
		ll resp = 1e9;
		for(auto it : mapa){
			ll y = it.first, qtd = it.second;
			resp = min(resp,count(n,y)/qtd);
		}
		printf("Case %lld: %lld\n",tc,resp);
	}
	return 0;
}