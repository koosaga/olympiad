#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, a[100005], c[100005];
vector<int> gph[100005];
lint ret;

int indeg[100005], vis[100005];
vector<int> dfn;

void dfs(int x){
	if(vis[x]) return;
	dfn.push_back(x);
	vis[x] = 1;
	for(auto &i : gph[x]){
		dfs(i);
	}
}

void solve(int x){
	dfn.clear();
	dfs(x);
	bool fnd = 0;
	int mincost = 1e9;
	for(auto &i : dfn){
		mincost = min(mincost, c[i]);
		if(!indeg[i]) fnd = 1;
		int mx = 0;
		for(auto &j : gph[i]){
			ret += c[j];
			mx = max(mx, c[j]);
		}
		ret -= mx;
	}
	if(!fnd){
		ret += mincost;
		return;
	}
	int upd = 1e9;
	for(auto &i : dfn){
		if(!indeg[i]) continue;
		int maxv = 0, maxvwo = 0;
		for(auto &j : gph[i]){
			maxv = max(maxv, c[j]);
			if(!indeg[j]) maxvwo = max(maxvwo, c[j]);
		}
		upd = min(upd, maxv - maxvwo);
	}
	ret += upd;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d %d",&a[i], &c[i]);
		indeg[a[i]]++;
		gph[a[i]].push_back(i);
	}
	queue<int> q;
	for(int i=1; i<=n; i++){
		if(!indeg[i]){
			q.push(i);
		}
	}
	while(!q.empty()){
		int x = q.front();
		q.pop();
		indeg[a[x]]--;
		if(indeg[a[x]] == 0){
			q.push(a[x]);
		}
	}
	int cnt = 0;
	for(int i=1; i<=n; i++){
		if(indeg[i] && !vis[i]) solve(i), cnt++;
	}
	if(cnt == 1 && count(indeg + 1, indeg + n + 1, 1) == n){
		ret = 0;
	}
	cout << ret << endl;
}
