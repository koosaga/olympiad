#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
 
int n;
vector<int> gph[250005];
int sz[250005], maxsz[250005];
 
void dfs(int x, int p){
	sz[x] = 1;
	maxsz[x] = 0;
	for(auto &i : gph[x]){
		if(i == p) continue;
		dfs(i, x);
		sz[x] += sz[i];
		maxsz[x] = max(maxsz[x], sz[i]);
	}
}
 
lint dfs2(int x, int p, int d){
	sz[x] = 1;
	lint ret = d;
	for(auto &i : gph[x]){
		if(i == p) continue;
		ret += dfs2(i, x, d+1);
		sz[x] += sz[i];
	}
	return ret;
}
 
int cnt[250005];
int dp[125005], aux[125005];
 
lint solve(int r){
	lint ret = 0;
	memset(cnt, 0, sizeof(cnt));
	memset(dp, 0, sizeof(dp));
	for(auto &i : gph[r]){
		ret += dfs2(i, r, 1);
		cnt[sz[i]]++;
	}
	dp[0] = 1;
	for(int i=1; i<=n/2; i++){
		if(cnt[i]){
			for(int j=0; j<=n/2; j++){
				aux[j] = dp[j];
				if(j >= i) aux[j] += aux[j - i];
			}
			for(int j=i; j<=n/2; j++){
				int sum = aux[j] - ((j >= i * cnt[i] + i) ? aux[j - i * (cnt[i] + 1)] : 0);
				if(sum) dp[j] = 1;
			}
		}
	}
	int p = 0;
	for(int i=0; i<=n/2; i++) if(dp[i]) p = i;
	return ret + 1ll * p * (n-1-p);
}
 
int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, 0);
	lint ret = 0;
	for(int i=1; i<=n; i++){
		int p = max(n - sz[i], maxsz[i]);
		if(p <= n/2) ret = max(ret, solve(i));
	}
	printf("%d %lld\n", n-1, ret);
}