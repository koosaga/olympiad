// Ivan Carvalho
// Solution to https://dmoj.ca/problem/year2015p5
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> ii;
typedef bitset<2010> bt;

const int MAXN = 2010;
const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;
const ll prime1 = 999983;
const ll prime2 = 999979;

bt chega[MAXN];
ll pot[2][MAXN],resposta;
char entrada[MAXN],palavras[MAXN];
set<ii> existe[MAXN];
int N,M;

int main(){

	pot[0][0] = pot[0][1] = 1;
	for(int i = 1;i<MAXN;i++){
		pot[0][i] = (pot[0][i-1]*prime1) % MOD1;
		pot[1][i] = (pot[1][i-1]*prime2) % MOD2;
	}

	scanf("%s",entrada);
	N = strlen(entrada);
	//printf("N %d E %s\n",N,entrada);
	scanf("%d",&M);

	while(M--){
		scanf("%s",palavras);
		int K = strlen(palavras);
		ll hash1 = 0, hash2 = 0;
		for(int i = 1;i<=K;i++){
			hash1 = (hash1 + pot[0][i]*palavras[i-1]) % MOD1;
			hash2 = (hash2 + pot[1][i]*palavras[i-1]) % MOD2;
		}
		existe[K].insert(ii(hash1,hash2));
	}

	//printf("N %d N - 1 %d\n",N,N-1);
	chega[N].set(N);
	for(int comeco = N - 1;comeco>=0;comeco--){
		ll hash1 = 0, hash2 = 0;
		for(int i = comeco, tam = 1;i < N;i++,tam++){

			hash1 = (hash1 + pot[0][tam]*entrada[i]) % MOD1;
			hash2 = (hash2 + pot[1][tam]*entrada[i]) % MOD2;
			ii meupar = ii(hash1,hash2);

			//if(chega[comeco].count(i)) continue;

			if(existe[tam].count(meupar)){
				chega[comeco] |= chega[i+1];
			}

		}
		resposta += chega[comeco].count();
		//printf("I %d : ",comeco);
		//for(int i = 0;i<=N;i++){
		//	if(chega[comeco].test(i)) printf("1");
		//	else printf("0");
		//}
		//printf("\n");
		chega[comeco].set(comeco);
	}

	printf("%lld\n",resposta);

	return 0;

}