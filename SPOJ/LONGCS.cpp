// Ivan Carvalho
// Solution to https://www.spoj.com/problems/LONGCS/
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
const int MAXN = 1e4 + 10;
const int MAXK = 10;
char entrada[MAXK][MAXN];
ll hash1[MAXK][MAXN],pot1[MAXN],invpot1[MAXN],hash2[MAXK][MAXN],pot2[MAXN],invpot2[MAXN];
int tamanhos[MAXK],K;
ll get_hash1(int id,int a,int b){
	ll val = ((hash1[id][b] - hash1[id][a-1])*invpot1[a-1]) % MOD1;
	if(val < 0) val += MOD1;
	return val; 
}
ll get_hash2(int id,int a,int b){
	ll val = ((hash2[id][b] - hash2[id][a-1])*invpot2[a-1]) % MOD2;
	if(val < 0) val += MOD2;
	return val; 
}
int check(int sz){
	vector<ii> truque[2];
	for(int i = 1,j = sz;i<=tamanhos[0];i++,j++){
		ll val1 = get_hash1(0,i,j);
		ll val2 = get_hash2(0,i,j);
		truque[1].push_back(ii(val1,val2));
	}
	for(int k = 1;k < K && !truque[1].empty();k++){
		sort(truque[1].begin(),truque[1].end());
		truque[1].erase(unique(truque[1].begin(),truque[1].end()),truque[1].end());
		swap(truque[0],truque[1]);
		truque[1].clear();
		for(int i = 1,j = sz;i<=tamanhos[k];i++,j++){
			ll val1 = get_hash1(k,i,j);
			ll val2 = get_hash2(k,i,j);
			ii davez = ii(val1,val2);
			if(binary_search(truque[0].begin(),truque[0].end(),davez)) truque[1].push_back(davez);
		}
	}
	return !truque[1].empty();
}
int main(){
	pot1[0] = pot2[0] = invpot1[0] = invpot2[0] = 1;
	for(int i = 1;i<MAXN;i++){
		pot1[i] = (pot1[i-1]*prime1) % MOD1;
		invpot1[i] = (invpot1[i-1]*invprime1) % MOD1;
		pot2[i] = (pot2[i-1]*prime2) % MOD2;
		invpot2[i] = (invpot2[i-1]*invprime2) % MOD2;
	}
	int TC;
	scanf("%d",&TC);
	while(TC--){
		scanf("%d",&K);
		int menor = MAXN;
		for(int k = 0;k<K;k++){
			scanf("%s",entrada[k]);
			tamanhos[k] = strlen(entrada[k]);
			menor = min(menor,tamanhos[k]);
			for(int i = 1;i<=tamanhos[k];i++){
				hash1[k][i] = (hash1[k][i-1] + entrada[k][i-1]*pot1[i]) % MOD1;
				hash2[k][i] = (hash2[k][i-1] + entrada[k][i-1]*pot2[i]) % MOD2;
			}
		}
		int ini = 1,fim = menor,resp = 0,meio;
		while(ini <= fim){
			meio = (ini+fim)/2;
			if(check(meio)){
				resp = meio;
				ini = meio + 1;
			}
			else{
				fim = meio - 1;
			}
		}
		printf("%d\n",resp);
	}
	return 0;
}