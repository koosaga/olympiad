// Ivan Carvalho
// Solution to https://www.spoj.com/problems/NICEDAY/
#include <cstdio>
#include <algorithm>
#define MAXN 100010
#define LIMIT 100000000
#define LSOne(S) (S & (-S))
using namespace std;
int primeiro[MAXN],segundo[MAXN],bit[MAXN],n,resposta;
void update(int idx, int val){
	while(idx <= n){
		bit[idx] = min(bit[idx],val);
		idx += LSOne(idx);
	}
}
int query(int idx){
	int ans = LIMIT;
	while(idx > 0){
		ans = min(ans,bit[idx]);
		idx -= LSOne(idx);
	}
	return ans;
}
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		resposta = 0;
		scanf("%d",&n);
		bit[0] = LIMIT;
		for(int i=1;i<=n;i++){
			int a,b,c;
			scanf("%d %d %d",&a,&b,&c);
			primeiro[a] = b;
			segundo[a] = c;
			bit[i] = LIMIT;
		}
		for(int i= 1;i <= n;i++){
			if (segundo[i] < query(primeiro[i])){
				resposta++;
				update(primeiro[i],segundo[i]);
			}
		}
		printf("%d\n",resposta);
	}
	return 0;
}