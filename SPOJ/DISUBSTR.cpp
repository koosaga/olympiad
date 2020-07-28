// Ivan Carvalho
// Solution to https://www.spoj.com/problems/DISUBSTR/
#include <cstdio>
#include <cstring>
#include <set>
#define MP make_pair
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
const ll MOD1 = 1e9 + 9;
const ll prime1 = 999983;
const ll MOD2 = 1e9 + 7;
const ll prime2 = 999979;
const ll invprime1 = 943912055;
const ll invprime2 = 672490127;
const int MAXN = 5010;
int N;
char entrada[MAXN];
ll pot1[MAXN],pot2[MAXN],hash1[MAXN],hash2[MAXN],inv1[MAXN],inv2[MAXN];
inline int func(int k){
	set<ii> valores;
	for(int i = 1, j = k;j <= N;i++,j++){
		ll val1 = ((hash1[j] - hash1[i-1])*inv1[i-1]) % MOD1;
		ll val2 = ((hash2[j] - hash2[i-1])*inv2[i-1]) % MOD2;
		if(val1 < 0){
			val1 += MOD1;
		}
		if(val2 < 0){
			val2 += MOD2;
		}
		valores.insert(MP(val1,val2));
	}
	return (int)valores.size();
}
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		pot1[0] = 1;
		pot2[0] = 1;
		inv1[0] = 1;
		inv2[0] = 1;
		scanf("%s",entrada);
		N = strlen(entrada);
		int resp = 0;
		for(int i=1;i<=N;i++){
			pot1[i] = (pot1[i-1]*prime1) % MOD1;
			pot2[i] = (pot2[i-1]*prime2) % MOD2;
			inv1[i] = (inv1[i-1]*invprime1) % MOD1;
			inv2[i] = (inv2[i-1]*invprime2) % MOD2;
			hash1[i] = (hash1[i-1] + entrada[i-1]*pot1[i]) % MOD1;
			hash2[i] = (hash2[i-1] + entrada[i-1]*pot2[i]) % MOD2;
		}
		for(int i=1;i<=N;i++) resp += func(i);
		printf("%d\n",resp);
	}
	return 0;
}