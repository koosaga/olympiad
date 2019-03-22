#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
using pi = pair<int, int>;
using lint = long long;

int n, vis[MAXN];
lint ans[MAXN];
vector<pi> gph[MAXN];
lint dpDown[MAXN], dpUp[MAXN], pae[MAXN];

void dfs3(int x, int p){
	for(auto &i : gph[x]){
		if(i.second != p){
			dfs3(i.second, x);
			dpDown[x] += dpDown[i.second] + i.first;
		}
		else{
			pae[x] = i.first;
		}
	}
}

void dfs4(int x, int p){
	for(auto &i : gph[x]){
		if(i.second != p){
			dpUp[i.second] = dpUp[x] + pae[i.second] + dpDown[x] - dpDown[i.second] - i.first;
			dfs4(i.second, x);
		}
	}
}

lint dfs2(int x, int p, vector<lint> &v){
	lint curmax = 0;
	for(auto &i : gph[x]){
		if(i.second != p && !vis[i.second]){
			lint nxt = dfs2(i.second, x, v) + i.first;
			if(curmax < nxt) swap(curmax, nxt);
			if(nxt) v.push_back(nxt);
		}
	}
	return curmax;
}

void solve(int r){
	lint cg = dpDown[r] + dpUp[r];
	vector<pair<lint, int>> tot;
	for(auto &i : gph[r]){
		if(!vis[i.second]){
			vector<lint> v;
			lint topv = dfs2(i.second, r, v);
			v.push_back(topv + i.first);
			for(auto &j : v) tot.emplace_back(j, i.second);
		}
	}
	sort(tot.rbegin(), tot.rend());
	{
		// case 1. includes root in selected vtx
		lint cursum = 0;
		for(int i=0; i<=tot.size(); i++){
			ans[i + 1] = min(ans[i + 1], cg - cursum);
			if(i < tot.size()) cursum += tot[i].first;
		}
	}
	{
		// case 2. two different vertices
		int hitpoint = tot.size();
		for(int i=0; i<tot.size(); i++){
			if(tot[i].second != tot[0].second){
				hitpoint = i;
				break;
			}
		}
		if(hitpoint == tot.size()) return;
		lint cursum = tot[hitpoint].first;
		for(int i=1; i<=hitpoint; i++){
			if(i > 1) ans[i] = min(ans[i], cg - cursum);
			cursum += tot[i-1].first;
		}
		for(int i=hitpoint + 1; i<=tot.size(); i++){
			ans[i] = min(ans[i], cg - cursum);
			if(i < tot.size()) cursum += tot[i].first;
		}
	}
}

vector<int> dfn;
int sz[MAXN], msz[MAXN];

void dfs(int x, int p){
	sz[x] = 1; msz[x] = 0;
	for(auto &i : gph[x]){
		if(!vis[i.second] && i.second != p){
			dfs(i.second, x);
			sz[x] += sz[i.second];
			msz[x] = max(msz[x], sz[i.second]);
		}
	}
	dfn.push_back(x);
}

int get_center(int x){
	dfs(x, -1);
	pi ret(1e9, 1e9);
	for(auto &i : dfn){
		int mx = max(msz[i], (int)dfn.size() - sz[i]);
		ret = min(ret, pi(mx, i));
	}
	dfn.clear();
	return ret.second;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int s, e, x, y; scanf("%d %d %d %d",&s,&e,&x,&y);
		gph[s].emplace_back(x, e);
		gph[e].emplace_back(y, s);
	}
	dfs3(1, -1);
	dfs4(1, -1);
	memset(ans, 0x3f, sizeof(ans));
	queue<int> que;
	que.push(1);
	while(!que.empty()){
		int x = que.front();
		que.pop();
		x = get_center(x);
		solve(x);
		vis[x] = 1;
		for(auto &i : gph[x]){
			if(!vis[i.second]){
				que.push(i.second);
			}
		}
	}
	int q; scanf("%d",&q);
	for(int i=2; i<=n; i++) ans[i] = min(ans[i-1], ans[i]);
	while(q--){
		int x; scanf("%d",&x); printf("%lld\n", ans[x]);
	}
}
