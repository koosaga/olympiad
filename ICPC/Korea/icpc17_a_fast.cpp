#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int mod = 1e9 + 7;
const int MAXN = 5005;
typedef pair<int, int> pi;

vector<int> gph[MAXN];
int n, chk[MAXN], par[MAXN], far[MAXN], dx[MAXN], dp[MAXN];

pi dfs(int x, int p){
	pi ret(0, x);
	for(auto &i : gph[x]){
		if(i != p){
			par[i] = x;
			auto t = dfs(i, x);
			ret = max(ret, pi(t.first + 1, t.second));
		}
	}
	return ret;
}

int dfs2(int x, int p){
	int ret = 0;
	for(auto &i : gph[x]){
		if(!chk[i] && i != p) ret = max(ret, dfs2(i, x) + 1);
	}
	return ret;
}

vector<int> v;

int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	int l = dfs(1, 0).second;
	int r = dfs(l, 0).second;
	for(int i=r; i!=l; i=par[i]) v.push_back(i);
	v.push_back(l);
	reverse(v.begin(), v.end());
	for(auto &i : v) chk[i] = 1;
	int d = v.size();
	for(int i=1; i<=d; i++){
		far[i] = dfs2(v[i-1], 0);
		if(far[i]){
			dx[i - far[i] + 1]++;
			dx[i + far[i]]--;
		}
	}
	for(int i=1; i<=d; i++) dx[i] += dx[i-1];
	int oddminv = 1e9, evenminv = 1e9;
	for(int i=1; i<=d; i++){
		dp[i] = 1e9;
		if(i % 2 == 1){
			if(dx[i] == 0) dp[i] = oddminv + i / 2;
			if(i > 1 && dx[i-1] == 0) evenminv = min(evenminv, dp[i-2] - (i-1)/2);
		}
		else{
			if(dx[i] == 0) dp[i] = evenminv + i / 2;
			if(i > 1 && dx[i-1] == 0) oddminv = min(oddminv, dp[i-2] - (i-1)/2);
		}
	}
	cout << min(dp[d], d/2) << endl;
}
