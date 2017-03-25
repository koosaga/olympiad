#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n;
char a[300005];
int sz[300005], msz[300005], vis[300005];
vector<int> gph[300005];
vector<int> dfn;

void dfs(int x, int p){
	dfn.push_back(x);
	sz[x] = 1;
	msz[x] = 0;
	for(auto &i : gph[x]){
		if(vis[i] || i == p) continue;
		dfs(i, x);
		msz[x] = max(msz[x], sz[i]);
		sz[x] += sz[i];
	}
}

int get_center(int x){
	dfn.clear();
	dfs(x, -1);
	int cur = 1e9;
	int ret = -1;
	for(auto &i : dfn){
		int w = max(msz[i], (int)dfn.size() - sz[i]);
		if(cur > w){
			cur = w;
			ret = i;
		}
	}
	return ret;
}

void dfs2(int x, int p, vector<int> &v, int dep, int mdep){
	if(a[x] == '(') dep++;
	else dep--;
	mdep = max(mdep, dep);
	if(mdep == dep) v.push_back(dep);
	for(auto &i : gph[x]){
		if(!vis[i] && i != p) dfs2(i, x, v, dep, mdep);
	}
}

void dfs3(int x, int p, vector<int> &v, int dep, int mdep){
	if(a[x] == '(') dep--;
	else dep++;
	mdep = max(mdep, dep);
	if(mdep == dep) v.push_back(dep);
	for(auto &i : gph[x]){
		if(!vis[i] && i != p) dfs3(i, x, v, dep, mdep);
	}
}

int cnt[300005];

lint getp(int x, vector<int> &l, vector<int> &r){
	lint ans = 0;
	for(auto &i : r) cnt[i]++;
	for(auto &i : l) ans += cnt[i];
	for(auto &i : r) cnt[i]--;
	return ans;
}

lint solve(int x){
	vector<int> l, r;
	lint sum = 0;
	int flg = (a[x] == '(' ? -1 : 1);
	for(auto &i : gph[x]){
		if(vis[i]) continue;
		vector<int> tl, tr;
		dfs2(i, x, tl, 0, 0);
		dfs3(i, x, tr, flg, max(flg, 0));
		for(auto &i : tl){
			l.push_back(i);
			if(flg == i) sum++;
		}
		for(auto &i : tr){
			r.push_back(i);
			if(i == 0) sum++;
		}
		sum -= getp(flg, tl, tr);
	}
	sum += getp(flg, l, r);
	return sum;
}

int main(){
	scanf("%d %s",&n,a+1);
	for(int i=1; i<n; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	queue<int> que;
	que.push(1);
	lint ans = 0;
	while(!que.empty()){
		int x = que.front();
		que.pop();
		x = get_center(x);
		ans += solve(x);
		vis[x] = 1;
		for(auto &i : gph[x]){
			if(!vis[i]) que.push(i);
		}
	}
	cout << ans;
}
