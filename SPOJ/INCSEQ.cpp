// Ivan Carvalho
// Solution to https://www.spoj.com/problems/INCSEQ/
#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))
using namespace std;
const int MOD = 5000000;
const int MAXN = 1e5 + 10;
const int MAXK = 51;
int vetor[MAXN],N,K;
struct FT{
	int bit[MAXN];
	void build(){memset(bit,0,sizeof(bit));}
	void update(int idx,int val){
		while(idx<MAXN){
			bit[idx] += val;
			bit[idx] %= MOD;
			idx += LSOne(idx);
		}
	}
	int query(int idx){
		int ans = 0;
		while(idx > 0){
			ans += bit[idx];
			ans %= MOD;
			idx -= LSOne(idx);
		}
		return ans;
	}
};
FT arvores[MAXK];
int main(){
	scanf("%d %d",&N,&K);
	for(int i = 1;i<=N;i++){
		scanf("%d",&vetor[i]);
		vetor[i]++;
	}
	for(int i = 1;i<=K;i++){
		arvores[i].build();
	}
	for(int i = 1;i<=N;i++){
		int x = vetor[i];
		arvores[1].update(x,1);
		for(int j = 1;j<=K;j++) arvores[j].update(x,arvores[j-1].query(x-1));
	}
	printf("%d\n",arvores[K].query(MAXN-1));
	return 0;
}