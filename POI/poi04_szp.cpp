#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
 
int n, a[1000005];
vector<int> gph[1000005];
 
int dp[1000005][2], indeg[1000005];
int chkv, chks;
 
int f(int x, int d){
	if(~dp[x][d]) return dp[x][d];
	int ret = d;
	int up = -1e8;
	for(auto &i : gph[x]){
		if(d == 0){
			ret += max(f(i, 0), f(i, 1));
		}
		else{
			ret += max(f(i, 0), f(i, 1));
			up = max(up, f(i, 0) - max(f(i, 0), f(i, 1)));
		}
	}
	if(x == chkv && chks == 0){
		up = max(up, 0);
	}
	if(d == 1) ret += up;
	if(ret < -1e8) ret = -1e8;
	return dp[x][d] = ret;
}
 
vector<int> lis;
 
void dfs(int x){
	lis.push_back(x);
	for(auto &i : gph[x]){
		dfs(i);
	}
}
 
int solve(int x){
	gph[a[x]].erase(find(gph[a[x]].begin(), gph[a[x]].end(), x));
	chkv = a[x];
	int ret = -1e9;
	lis.clear();
	dfs(x);
	for(chks = 0; chks <= 1; chks++){
		ret = max(ret, f(x, chks));
		for(auto &i : lis){
			dp[i][0] = dp[i][1] = -1;
		}
	}
	for(int i=x; indeg[i]; i=a[i]){
		indeg[i] = 0;
	}
	return ret;
}
 
int main(){
	memset(dp, -1, sizeof(dp));
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		indeg[a[i]]++;
		gph[a[i]].push_back(i);
	}
	queue<int> que;
	for(int i=1; i<=n; i++){
		if(!indeg[i]){
			que.push(i);
		}
	}
	while(!que.empty()){
		int x = que.front();
		que.pop();
		indeg[a[x]]--;
		if(indeg[a[x]] == 0){
			que.push(a[x]);
		}
	}
	int ret = 0;
	for(int i=1; i<=n; i++){
		if(indeg[i]){
			ret += solve(i);
		}
	}
	cout << ret << endl;
}