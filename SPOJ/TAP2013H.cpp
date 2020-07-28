// Ivan Carvalho
// Solution to https://www.spoj.com/problems/TAP2013H/
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 1e6 + 1;
int soma[MAXN],dp[MAXN];
vector<int> valores[MAXN];
int solve(int k){
	if(dp[k]) return dp[k];
	return dp[k] = 1 + solve(soma[k]);
}
int main(){
	for(int i=2;i<MAXN;i++){
		if(!soma[i]){
			dp[i] = 1;
			for(int j=2*i;j<MAXN;j += i){
				soma[j] += i;
			}
		}
	}
	for(int i=2;i<MAXN;i++){
		if(!dp[i]) solve(i);
	}
	for(int i=2;i<MAXN;i++){
		valores[dp[i]].push_back(i);
	}
	int Q;
	scanf("%d",&Q);
	while(Q--){
		int A,B,K;
		scanf("%d %d %d",&A,&B,&K);
		auto it = lower_bound(valores[K].begin(), valores[K].end(),A);
		if(it == valores[K].end() || (*it) > B){
			printf("0\n");
			continue;
		}
		auto rit = upper_bound(valores[K].begin(),valores[K].end(),B);
		rit--;
		if((*rit) < A){
			printf("0\n");
			continue;
		}
		int exibir = rit - it;
		printf("%d\n",exibir+1);
	}
	return 0;
}