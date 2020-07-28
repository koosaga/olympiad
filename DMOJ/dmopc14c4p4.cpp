// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc14c4p4
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
string hydra;
char entrada[MAXN],conversao[30],convertido[15],inverso[30];
vector<ii> pares;
ll hash1[MAXN],hash2[MAXN],pot1[MAXN],pot2[MAXN],inv1[MAXN],inv2[MAXN],N,M;
void constroi(ll i,ll j){
	ll val1 = ((hash1[j] - hash1[i-1])*(inv1[i-1])) % MOD1;
	if(val1 < 0) val1 += MOD1;
	ll val2 = ((hash2[j] - hash2[i-1])*(inv2[i-1])) % MOD2;
	if(val2 < 0) val2 += MOD2;
	pares.push_back(ii(val1,val2));
}
void todos(){
	for(ll i=1,j = 9;j<=N;i++,j++){
		constroi(i,j);
	}
	sort(pares.begin(),pares.end());
}
ii doQuery(){
	for(ll i=0;i<9;i++){
		convertido[i] = conversao[hydra[i] - 'A'];
	}
	ll val1 = 0;
	ll val2 = 0;
	for(ll i=1;i<=9;i++){
		val1 = (val1 + pot1[i]*convertido[i-1]) % MOD1;
		val2 = (val2 + pot2[i]*convertido[i-1]) % MOD2;
	}
	return ii(val1,val2);
}
int main(){
	scanf("%s",entrada);
	N = strlen(entrada);
	if(N < 9){
		printf("KeyNotFoundError\n");
		return 0;
	}
	pot1[0] = pot2[0] = inv1[0] = inv2[0] = 1;
	for(ll i=1;i<=N;i++){
		pot1[i] = (pot1[i-1]*prime1)%MOD1;
		pot2[i] = (pot2[i-1]*prime2)%MOD2;
		inv1[i] = (inv1[i-1]*invprime1)%MOD1;
		inv2[i] = (inv2[i-1]*invprime2)%MOD2;
		hash1[i] = (hash1[i-1] + pot1[i]*entrada[i])%MOD1;
		hash2[i] = (hash2[i-1] + pot2[i]*entrada[i])%MOD2;
	}
	scanf("%lld",&M);
	hydra = "HAILHYDRA";
	todos();
	while(M--){
		scanf("%s",conversao);
		ii davez = doQuery();
		if(binary_search(pares.begin(),pares.end(),davez)){
			for(ll i=0;i<26;i++){
				inverso[conversao[i] - 'A'] = 'A' + i;
			}
			for(ll i=0;i<N;i++) entrada[i] = inverso[entrada[i] - 'A'];
			printf("%s\n",entrada);
			return 0;
		}
	}
	printf("KeyNotFoundError\n");
	return 0;
}0;
}