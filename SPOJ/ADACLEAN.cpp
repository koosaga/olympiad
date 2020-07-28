// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADACLEAN/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
const ll MOD1 = 1e9 + 9;
const ll prime1 = 999983;
const ll MOD2 = 1e9 + 7;
const ll prime2 = 999979;
const ll invprime1 = 943912055;
const ll invprime2 = 672490127;
const int MAXN = 100011;
ll pot1[MAXN],inv1[MAXN],pot2[MAXN],inv2[MAXN],hash1[MAXN],hash2[MAXN];
char entrada[MAXN];
inline ii query(ll ini,ll fim){
	ll val1 = ((hash1[fim] - hash1[ini-1])*inv1[ini-1]) % MOD1;
	if(val1 < 0) val1 += MOD1;
	ll val2 = ((hash2[fim] - hash2[ini-1])*inv2[ini-1]) % MOD2;
	if(val2 < 0) val2 += MOD2;
	return ii(val1,val2);
}
int main(){
	pot1[0] = pot2[0] = inv1[0] = inv2[0] = 1LL;  
	for(ll i = 1;i<MAXN;i++){
		pot1[i] = (pot1[i-1]*prime1) % MOD1;
		pot2[i] = (pot2[i-1]*prime2) % MOD2;
		inv1[i] = (inv1[i-1]*invprime1) % MOD1;
		inv2[i] = (inv2[i-1]*invprime2) % MOD2;
	}
	ll T;
	scanf("%lld",&T);
	while(T--){
		ll N,K;
		scanf("%lld %lld",&N,&K);
		scanf("%s",entrada);
		for(ll i = 1;i<=N;i++){
			hash1[i] = (hash1[i-1] + entrada[i-1]*pot1[i]) % MOD1;
			hash2[i] = (hash2[i-1] + entrada[i-1]*pot2[i]) % MOD2;
		}
		vector<ii> pares;
		for(ll i = 1,j = K;j <= N;i++,j++) pares.push_back(query(i,j));
		sort(pares.begin(),pares.end());
		pares.erase(unique(pares.begin(),pares.end()),pares.end());
		printf("%lld\n",(ll)pares.size());
	}
	return 0;
}