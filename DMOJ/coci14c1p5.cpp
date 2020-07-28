// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c1p5
#include <bits/stdc++.h>
#define gc getchar_unlocked
inline void getint(int &x){
   int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
typedef long long ll;
const int MAXN = 1e6 + 10;
const int MAXK = 502;
const int MAXM = 102;
int N,M,K;
ll precalc[MAXM][MAXK];
ll tab[MAXM][MAXK];
int tamanhos[MAXM];
ll solve(int atual,int restam){
	if(atual == M+1){
		return 0;
	}
	if(tab[atual][restam] != -1) return tab[atual][restam];
	ll best = 1e18;
	for(int usa = 0;usa<=restam;usa++){
		best = min(best, precalc[atual][usa] + solve(atual+1,restam - usa) );
	}
	return tab[atual][restam] = best;
}
inline ll somatorio(ll n) {
   if(n & 1) return ((n+1)/2)*n;
   return (n/2)*(n+1);
}

inline ll custo(ll n, ll k) {
    int v1 = n / k;
    int v2 = (n + k - 1) / k;
    int v3 = n % k;
    int v4 = k - v3;
    return v4 * somatorio(v1) + v3 * somatorio(v2);
}
int main(){
	scanf("%d %d %d",&N,&M,&K);
	for(int i = 1;i<=N;i++){
		int x;
		getint(x);
		tamanhos[x]++;
	}
	for(int i = 1;i<=M;i++){
		for(int k = 0;k<=K;k++){
			precalc[i][k] = custo(tamanhos[i],k+1);
		}
	}
	memset(tab,-1,sizeof(tab));
	printf("%lld\n",solve(1,K));
	return 0;
}