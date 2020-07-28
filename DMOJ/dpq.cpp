// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dpq
#include <bits/stdc++.h>
#define LSOne(S) ((S) & (-S))
using namespace std;

typedef long long ll;

const int MAXN = 2*1e5 + 10;

ll bit[MAXN],dp[MAXN];
ll h[MAXN],a[MAXN];
int N;

void update(int x, ll val){
	while(x <= N){
		bit[x] = max(bit[x],val);
		x += LSOne(x);
	}
}

ll query(int x){

	ll ans = 0;
	while(x > 0){
		ans = max(ans,bit[x]);
		x -= LSOne(x);
	}

	return ans;

}

int main(){

	scanf("%d",&N);

	for(int i = 1;i<=N;i++){
		scanf("%lld",&h[i]);
	}
	for(int i = 1;i<=N;i++){
		scanf("%lld",&a[i]);
	}

	for(int i = 1;i<=N;i++){
		dp[i] = query(h[i] - 1) + a[i];
		update(h[i],dp[i]);
	}

	ll best = 0;
	for(int i = 1;i<=N;i++) best = max(best,dp[i]);
	printf("%lld\n",best);

	return 0;

}