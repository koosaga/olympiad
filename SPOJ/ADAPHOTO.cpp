// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADAPHOTO/
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
const int MAXN = 1e6 + 10;
char entrada[2][MAXN];
bitset<MOD1 + 2> conjunto1,conjunto2;
ll hash1[2][MAXN],pot1[MAXN],invpot1[MAXN],hash2[2][MAXN],pot2[MAXN],invpot2[MAXN];
int N,M;
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
	for(int i = 1,j = sz;j<=N;i++,j++){
		conjunto1.set(get_hash1(0,i,j),1);
	}
	vector<ii> correspondidos;
	for(int i = 1,j = sz;j<=M;i++,j++){
		ll val1 = get_hash1(1,i,j);
		if(conjunto1.test(val1)){
			conjunto2.set(val1,1);
			ll val2 = get_hash2(1,i,j);
			correspondidos.push_back(ii(val1,val2));
		}
	}
	sort(correspondidos.begin(),correspondidos.end());
	correspondidos.erase(unique(correspondidos.begin(),correspondidos.end()),correspondidos.end());
	int flag = 0;
	for(int i = 1,j = sz;j<=N;i++,j++){
		ll val1 = get_hash1(0,i,j);
		conjunto1.set(val1,0);
		if(conjunto2.test(val1)){
			ll val2 = get_hash2(0,i,j);
			flag |= binary_search(correspondidos.begin(),correspondidos.end(),ii(val1,val2));
		}
	}
	for(int i = 0;i<correspondidos.size();i++){
		conjunto2.set(correspondidos[i].first,0);
	}
	return flag;
}
int main(){
	scanf("%s",entrada[0]);
	scanf("%s",entrada[1]);
	N = strlen(entrada[0]);
	M = strlen(entrada[1]);
	pot1[0] = invpot1[0] = pot2[0] = invpot2[0] = 1;
	for(int i = 1;i<=max(N,M);i++){
		pot1[i] = (pot1[i-1]*prime1) % MOD1;
		invpot1[i] = (invpot1[i-1]*invprime1) % MOD1;
		pot2[i] = (pot2[i-1]*prime2) % MOD2;
		invpot2[i] = (invpot2[i-1]*invprime2) % MOD2;
	}
	for(int i = 1;i<=N;i++){
		hash1[0][i] = (hash1[0][i-1] + entrada[0][i-1]*pot1[i]) % MOD1;
		hash2[0][i] = (hash2[0][i-1] + entrada[0][i-1]*pot2[i]) % MOD2;
	}
	for(int i = 1;i<=M;i++){
		hash1[1][i] = (hash1[1][i-1] + entrada[1][i-1]*pot1[i]) % MOD1;
		hash2[1][i] = (hash2[1][i-1] + entrada[1][i-1]*pot2[i]) % MOD2;
	}
	int ini = 1, fim = min(N,M),resp = 0,meio;
	while(ini <= fim){
		meio = (ini+fim)/2;
		if(check(meio)){
			ini = meio + 1;
			resp = meio;
		}
		else{
			fim = meio - 1;
		}
	}
	printf("%d\n",resp);
	return 0;
}