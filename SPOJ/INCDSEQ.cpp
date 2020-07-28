// Ivan Carvalho
// Solution to https://www.spoj.com/problems/INCDSEQ/
#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))
using namespace std;
const int MAXN = 1e4 + 10;
const int MOD = 5000000;
const int MAXK = 51;
int bit[MAXN][MAXK],N,K,vetor[MAXN];
vector<int> comp;
map<int,int> anterior[MAXN];
void update(int idx,int k,int delta){
	while(idx < MAXN){
		bit[idx][k] += delta;
		bit[idx][k] %= MOD;
		idx += LSOne(idx);
	}
}
int read(int idx,int k){
	if(k == 0) return 1;
	int ans = 0;
	while(idx > 0){
		ans += bit[idx][k];
		ans %= MOD;
		idx -= LSOne(idx);
	}
	return ans;
}
int main(){
	scanf("%d %d",&N,&K);
	for(int i = 1;i<=N;i++){
		scanf("%d",&vetor[i]);
		comp.push_back(vetor[i]);
	}
	sort(comp.begin(),comp.end());
	comp.erase(unique(comp.begin(),comp.end()),comp.end());
	for(int i = 1;i<=N;i++){
		int x = lower_bound(comp.begin(),comp.end(),vetor[i]) - comp.begin() + 1;
		for(int k = 0;k<K;k++){
			int velho = anterior[x][k];
			int novo = read(x-1,k);
			int delta = (novo - velho) % MOD;
			anterior[x][k] = novo;
			update(x,k+1,delta);
		}
	}
	int exibe = read(MAXN-1,K);
	if(exibe < 0) exibe += MOD;
	printf("%d\n",exibe);
	return 0;
}