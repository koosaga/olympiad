#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 100005;

vector<int> gph[MAXN];
vector<int> dfn;
int n, deg[MAXN], dist[MAXN], ret[MAXN], vis[MAXN], hitmax;
int sz[MAXN], msz[MAXN], dxV[MAXN];

struct query{
	int dist, value;
};

void dfs3(int x, int p, int d, vector<query> &quer){
	hitmax = max(hitmax, d);
	quer.push_back({dist[x] - d, deg[x]});
	for(auto &i : gph[x]){
		if(i != p && !vis[i]){
			dfs3(i, x, d + 1, quer);
		}
	}
}

void dfs4(int x, int p, int d){
	ret[x] += dxV[d];
	for(auto &i : gph[x]){
		if(i != p && !vis[i]){
			dfs4(i, x, d + 1);
		}
	}
}

void DoArray(vector<query> q, int coeff){
	if(coeff == 1){
		for(auto &i : q){
			if(i.dist > hitmax) continue;
			dxV[max(i.dist, 0)] += i.value;
		}
		for(int i=1; i<=hitmax; i++) dxV[i] += dxV[i-1];
	}
	if(coeff == -1){
		for(int i=0; i<=hitmax; i++) dxV[i] = 0;
		hitmax = 1;
	}
}

void solve(int r){
	vector<query> quers;
	int myHitMax = 1;
	for(auto &i : gph[r]){
		if(vis[i]) continue;
		vector<query> tquers;
		dfs3(i, r, 1, tquers);
		for(auto &i : tquers){
			quers.push_back(i);
			i.value *= -1;
		}
		DoArray(tquers, 1);
		dfs4(i, r, 1);
		myHitMax = max(myHitMax, hitmax);
		DoArray(tquers, -1);
	}
	quers.push_back({dist[r], deg[r]});
	hitmax = myHitMax;
	DoArray(quers, 1);
	dfs4(r, -1, 0);
	DoArray(quers, -1);
}

void dfs2(int x, int p){
	dfn.push_back(x);
	sz[x] = 1;
	msz[x] = 0;
	for(auto &i : gph[x]){
		if(!vis[i] && i != p){
			dfs2(i, x);
			sz[x] += sz[i];
			msz[x] = max(msz[x], sz[i]);
		}
	}
}

int get_center(int x){
	dfn.clear();
	dfs2(x, -1);
	pi ret(1e9, 1e9);
	for(auto &i : dfn){
		int x = max(msz[i], (int)dfn.size() - sz[i]);
		ret = min(ret, pi(x, i));
	}
	return ret.second;
}

int main(){
	scanf("%d",&n);
	fill(deg + 1, deg + n + 1, 2);
	for(int i=1; i<n; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
		deg[s]--; deg[e]--;
	}
	memset(dist, 0x3f, sizeof(dist));
	queue<int> que;
	for(int i=1; i<=n; i++){
		if(deg[i] == 1){
			que.push(i);
			dist[i] = 0;
		}
	}
	while(!que.empty()){
		int x = que.front();
		que.pop();
		for(auto &i : gph[x]){
			if(dist[i] > dist[x] + 1){
				que.push(i);
				dist[i] = dist[x] + 1;
			}
		}
	}
	que.push(1);
	while(!que.empty()){
		int x = que.front();
		que.pop();
		x = get_center(x);
		solve(x);
		vis[x] = 1;
		for(auto &i : gph[x]){
			if(!vis[i]) que.push(i);
		}
	}
	for(int i=1; i<=n; i++){
		if(deg[i] == 1) ret[i] = 1;
		printf("%d\n", ret[i]);
	}
}
