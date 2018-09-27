#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10005;

int n;
vector<int> gph[MAXN];
vector<int> dfn;

int dp[MAXN];

int query(int k){
	for(auto &i : dfn){
		if(i == 1) break;
		vector<int> v;
		for(auto &j : gph[i]) v.push_back(dp[j] + 1);
		if(v.size() % 2 == 0) v.push_back(0);
		sort(v.begin(), v.end());
		auto trial_pos = [&](int x){
			int l = 0, r = v.size() - 1;
			for(int i=0; i<v.size()/2; i++){
				if(l == x) l++;
				if(r == x) r--;
				if(v[l] + v[r] > k) return 0;
			}
			return 1;
		};
		int s = 0, e = v.size();
		while(s != e){
			int m = (s+e)/2;
			if(trial_pos(m)) e = m;
			else s = m + 1;
		}
		if(s == v.size()) return 0;
		dp[i] = v[s];
	}
	vector<int> v;
	for(auto &i : gph[1]) v.push_back(dp[i] + 1);
	sort(v.begin(), v.end());
	if(v.back() > k) return 0;
	if(v.size() % 2 == 1) v.pop_back();
	for(int i=0; i<v.size()/2; i++){
		if(v[i] + v[v.size()-i-1] > k) return 0;
	}
	return 1;
}

void dfs(int x){
	dfn.push_back(x);
	for(auto &i : gph[x]){
		gph[i].erase(find(gph[i].begin(), gph[i].end(), x));
		dfs(i);
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1);
	int ans = n - 1;
	for(int i=1; i<=n; i++){
		ans -= ((i != 1) + gph[i].size()) / 2;
	}
	int s = 1, e = n;
	reverse(dfn.begin(), dfn.end());
	while(s != e){
		int m = (s+e)/2;
		if(!query(m)) s = m+1;
		else e = m;
	}
	printf("%d %d\n", ans, s);
}
