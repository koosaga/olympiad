// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADASQR/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5012;
typedef unsigned long long ll;
typedef pair<int,ll> ii;
const ll MOD = 1e9 + 7;
ll N,K;
ll matriz[MAXN][MAXN];
ll vetor[MAXN];
ll soma;
int main(){
	scanf("%lld %lld",&N,&K);
	for(int linha = 1;linha<=N;linha++){
		ll x0,a,b,c;
		scanf("%lld %lld %lld %lld",&x0,&a,&b,&c);
		a %= c;b %= c;
		vetor[1] = x0;
		for(int i = 2;i<=N;i++){
			__int128 seraquevai = ((__int128)a*(__int128)vetor[i-1] + (__int128)b) % (__int128)c;
			vetor[i] = (ll)seraquevai;
		}
		deque<ii> fila;
		for(int i = 1;i<K;i++){
			ll davez = vetor[i];
			while(!fila.empty() && davez < fila.back().second) fila.pop_back();
			fila.push_back(ii(i,davez));
		}
		for(int i = K,j = 1;i<=N;i++,j++){
			if(!fila.empty() && fila.front().first == i - K) fila.pop_front();
			ll davez = vetor[i];
			while(!fila.empty() && davez < fila.back().second) fila.pop_back();
			fila.push_back(ii(i,davez));
			matriz[linha][j] = fila.front().second;
		}
	}
	for(int coluna = 1;coluna <= N - K + 1;coluna++){
		deque<ii> fila;
		for(int i = 1;i<K;i++){
			ll davez = matriz[i][coluna];
			while(!fila.empty() && davez < fila.back().second) fila.pop_back();
			fila.push_back(ii(i,davez));
		}
		for(int i = K;i<=N;i++){
			if(!fila.empty() && fila.front().first == i - K) fila.pop_front();
			ll davez = matriz[i][coluna];
			while(!fila.empty() && davez < fila.back().second) fila.pop_back();
			fila.push_back(ii(i,davez));
			soma = (soma + (fila.front().second)) % MOD;
		}
	}
	printf("%lld\n",soma);
	return 0;
} 