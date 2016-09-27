#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

vector<int> gph[300005];
int n, a, b;
int par[300005], chk[300005], dp[300005];

void dfs(int x, int p){
	for(auto &i : gph[x]){
		if(i != p){
			par[i] = x;
			dfs(i, x);
		}
	}
}

void getdp(int x, int p){
	vector<int> v;
	for(auto &i : gph[x]){
		if(i != p){
			getdp(i, x);
			v.push_back(dp[i]);
		}
	}
	sort(v.begin(), v.end());
	for(int i=0; i<v.size(); i++){
		dp[x] = max(dp[x], v[i] + (int)v.size() - i);
	}
}

vector<int> dpl[300005];

int solve(int x, int l, int p){
	if(l < 0) return 0;
	int nxt = -1;
	for(auto &i : gph[x]){
		if(i == p) continue;
		if(chk[i]) nxt = i;
	}
	int val = l - 1;
	for(int i=0; i<dpl[x].size(); i++){
		if(l - i - 1 < dpl[x][i]){
			return 0;
		}
		if(l - i - 1 == dpl[x][i]){
			val = l - i - 2;
		}
	}
	if(nxt == -1) return 1;
	return solve(nxt, val, x) + 1;
}

int main(){
	int len = 0;
	cin >> n >> a >> b;
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(a, -1);
	for(int i=b; i; i=par[i]){
		chk[i] = 1;
		len++;
	}
	for(int i=b; i; i=par[i]){
		for(auto &j : gph[i]){
			if(!chk[j]){
				getdp(j, i);
				dpl[i].push_back(dp[j]);
			}
		}
		sort(dpl[i].begin(), dpl[i].end());
		reverse(dpl[i].begin(), dpl[i].end());
	}
	int s = 0, e = n;
	while(s != e){
		int m = (s+e)/2;
		if(solve(a, m, -1) + solve(b, m, -1) >= len) e = m;
		else s = m+1;
	}
	cout << s;
}

