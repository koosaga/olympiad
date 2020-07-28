// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c1p3
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXL = 1e6 + 10;
const int MAXK = 5*1e5 + 10;

char entrada[MAXL],letra[MAXK];
ll somatorio[2*MAXL],tam,K;
ll exibe[MAXK],linha[MAXK];

ll triangular(ll val){
	ll v1 = val;
	ll v2 = val + 1;
	if(v1 % 2 == 0) v1 /= 2;
	else v2 /= 2;
	v1 %= tam;
	v2 %= tam;
	return (v1*v2) % tam;
}

ll calcula(int a,int b){
	if(a > b) return 0;
	ll ans = somatorio[b];
	if(a != 0) ans -= somatorio[a-1];
	return ans;
}

int main(){
	scanf("%lld",&K);
	scanf("%s",entrada);
	tam = strlen(entrada);
	scanf("%lld",&K);
	for(ll i = 1;i<=K;i++){
		scanf("%lld %c",&linha[i],&letra[i]);
	}
	for(char c = 'A';c<='Z';c++){
		for(ll i = 0;i<tam;i++){
			somatorio[i] = (entrada[i] == c);
			somatorio[i+tam] = somatorio[i];
		}
		for(ll i = 1;i<2*tam;i++){
			somatorio[i] += somatorio[i-1];
		}
		for(ll i = 1;i<=K;i++){
			if(letra[i] != c) continue;
			ll comeca = triangular(linha[i] - 1);
			exibe[i] = (linha[i]/tam)*somatorio[tam-1];
			exibe[i] += calcula(comeca,comeca + (linha[i] % tam) - 1);
		}
	}
	for(ll i = 1;i<=K;i++) printf("%lld\n",exibe[i]);
	return 0;
}