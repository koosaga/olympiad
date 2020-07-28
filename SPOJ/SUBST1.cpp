// Ivan Carvalho
// Solution to https://www.spoj.com/problems/SUBST1/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD1 = 1e9 + 9;
const ll prime1 = 999983;
const ll MOD2 = 1e9 + 7;
const ll prime2 = 999979;
const ll invprime1 = 943912055;
const ll invprime2 = 672490127;
const int MAXN = 5*1e4 + 10;
char entrada[MAXN];
int N,logaritmo[MAXN];
ll hash1[MAXN],pot1[MAXN],invpot1[MAXN],resposta;
vector<int> SArray;
inline ll get_hash1(int a,int b){
	ll val = ((hash1[b] - hash1[a-1])*invpot1[a-1]) % MOD1;
	if(val < 0) val += MOD1;
	return val;
}
int LCP(int idx1,int idx2,int tam){
	for(int i = 0;i<=min(tam,10);i++){
		if(entrada[idx1-1+i] != entrada[idx2 - 1 + i]) return i;
		if(tam == i + 1) return tam;
	}
	int atual = 0;
	for(int i = logaritmo[tam];i>=0;i--){
		int novo = atual + (1 << i);
		if(novo <= tam && get_hash1(idx1,idx1+novo-1) == get_hash1(idx2,idx2+novo-1)){
			atual = novo;
		}
	}
	return atual;
}
int compara(int idx1,int idx2){
	int tam = N - max(idx1,idx2) + 1;
	int prefixo = LCP(idx1,idx2,tam);
	if(prefixo == tam) return idx1 > idx2;
	return entrada[idx1 + prefixo - 1] < entrada[idx2 + prefixo - 1];
}
template<class Iter>
void merge_sort(Iter first, Iter last){
    if (last - first > 1) {
        Iter middle = first + (last - first) / 2;
        merge_sort(first, middle); // [first, middle)
        merge_sort(middle, last);  // [middle, last)
        inplace_merge(first, middle, last,compara);
    }
}
int main(){
	pot1[0] = invpot1[0] = 1;
	for(int i = 1;i<MAXN;i++){
		logaritmo[i] = logaritmo[i/2] + 1;
		pot1[i] = (pot1[i-1]*prime1) % MOD1;
		invpot1[i] = (invpot1[i-1]*invprime1) % MOD1;
	}
	int TC;
	scanf("%d",&TC);
	while(TC--){	
		scanf("%s",entrada);
		N = strlen(entrada);
		resposta = 0;
		SArray.clear();
		pot1[0] = invpot1[0] = 1;
		for(int i = 1;i<=N;i++){
			SArray.push_back(i);
			hash1[i] = (hash1[i-1] + entrada[i-1]*pot1[i]) % MOD1;
		}
		merge_sort(SArray.begin(),SArray.end());
		for(int i = 0;i<N;i++){
			int idx = SArray[i];
			resposta += N - idx + 1;
			if(i != 0){
				int ant = SArray[i-1];
				resposta -= LCP(ant,idx, N - max(ant,idx) + 1 );
			}
		}
		printf("%lld\n",resposta);
	}
	return 0;
}