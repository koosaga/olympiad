#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;

int n, sz[MAXN], msz[MAXN], vis[MAXN];
int a[MAXN];
vector<int> dfn;
vector<pi> gph[MAXN];

void dfs(int x, int p){
	dfn.push_back(x);
	sz[x] = 1;
	msz[x] = 0;
	for(auto [j, i] : gph[x]){
		if(i != p && !vis[i]){
			dfs(i, x);
			sz[x] += sz[i];
			msz[x] = max(msz[x], sz[i]);
		}
	}
}

int get_center(int x){
	dfs(x, -1);
	pi ret(1e9, -1);
	for(auto &i : dfn){
		ret = min(ret, pi(max(sz[x] - sz[i], msz[i]), i));
	}
	dfn.clear();
	return ret.second;
}

struct node1{
	int frm, tank_sum, val;
};

struct node2{
	int frm, needy, val;
};

vector<node2> v2;
vector<node1> v1;

void dfs1(int x, int p, int cur, int src, int just_tank_hap, int dep){
	just_tank_hap += a[x];
	if(a[x] >= cur){
		assert(just_tank_hap >= 0);
		v1.push_back({src, just_tank_hap, dep});
	}
	cur = max(cur - a[x], 0);
	for(auto [w, v] : gph[x]){
		if(vis[v]) continue;
		if(v == p) continue;
		dfs1(v, x, cur + w, src, just_tank_hap - w, dep + 1);
	}
}

void dfs2(int x, int p, int cur, int val, int src, int dep){
	val += a[x];
	assert(cur <= 0);
	v2.push_back({src, -cur, dep});
	for(auto [w, v] : gph[x]){
		if(vis[v]) continue;
		if(v == p) continue;
		dfs2(v, x, min(cur, val - w), val - w, src, dep + 1);
	}
}

int lbl[MAXN];

int solve(int x){
//	printf("solving %d\n", x);
	v1.clear(); v2.clear();
	v1.push_back({n + 1, 0, 0});
	v2.push_back({n + 2, 0, 1});
	for(auto &i : gph[x]){
		if(vis[i.second]) continue;
		dfs1(i.second, x, i.first, i.second, -i.first, 1);
		dfs2(i.second, x, min(a[x] - i.first, 0), a[x] - i.first, i.second, 2);
	}
	sort(v1.begin(), v1.end(), [&](const node1 &a, const node1 &b){
		return a.tank_sum < b.tank_sum;
	});
	sort(v2.begin(), v2.end(), [&](const node2 &a, const node2 &b){
		return a.needy < b.needy;
	});
	for(auto &i : gph[x]) lbl[i.second] = 0;
	lbl[n+1] = lbl[n+2] = 0;
	int ret = 1;
	int ptr = 0;
	priority_queue<pi> pq;
	for(auto &i : v1){
		while(ptr < v2.size() && v2[ptr].needy <= i.tank_sum){
			lbl[v2[ptr].frm] = max(lbl[v2[ptr].frm], v2[ptr].val);
			pq.push(pi(lbl[v2[ptr].frm], v2[ptr].frm));
			ptr++;
		}
		if(pq.top().second != i.frm) ret = max(ret, i.val + pq.top().first);
		else{
			while(pq.top().second == i.frm) pq.pop();
			ret = max(ret, i.val + pq.top().first);
			pq.push(pi(lbl[i.frm], i.frm));
		}
	}
	return ret;
}


int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	for(int i=0; i<n-1; i++){
		int s, e, x; scanf("%d %d %d",&s,&e,&x);
		gph[s].emplace_back(x, e);
		gph[e].emplace_back(x, s);
	}
	int ret = 0;
	queue<int> que;
	que.push(1);
	while(!que.empty()){
		int x = que.front();
		que.pop();
		x = get_center(x);
		vis[x] = 1;
		ret = max(ret, solve(x));
		for(auto &i : gph[x]){
			if(!vis[i.second]){
				que.push(i.second);
			}	
		}
	}
	cout << ret << endl;
}
