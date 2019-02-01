#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, a[1000005], indeg[1000005];
bool vis[1000005];
vector<int> gph[1000005];

pi dfs1(int x){
	vis[x] = 1;
	pi ret(0, x);
	for(auto &i : gph[x]){
		pi v = dfs1(i);
		v.first++;
		ret = max(ret, v);
	}
	return ret;
}

vector<int> dfn;

void dfs2(int x){
	if(vis[x]) return;
	vis[x] = 1;
	dfn.push_back(x);
	for(auto &i : gph[x]){
		dfs2(i);
	}
	dfs2(a[x]);
}

int solve(int x){
	dfn.clear();
	dfs2(x);
	int ret = 0, cyc = 0;
	for(auto &i : dfn){
		if(indeg[i]){
			cyc++;
			gph[a[i]].erase(find(gph[a[i]].begin(), gph[a[i]].end(), i));
		}
	}
	for(auto &i : dfn){
		if(indeg[i]){
			ret = max(ret, dfs1(i).first);
		}
	}
	return ret + cyc;
}

int main(){
	cin >> n;
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		indeg[a[i]]++;
		gph[a[i]].push_back(i);
	}
	queue<int> que;
	for(int i=1; i<=n; i++){
		if(indeg[i] == 0) que.push(i);
	}
	while(!que.empty()){
		int x = que.front();
		que.pop();
		indeg[a[x]]--;
		if(indeg[a[x]] == 0) que.push(a[x]);
	}
	int ret = 0, path = 0;
	if(!indeg[1]){
		dfs2(1);
		for(auto &i : dfn){
			if(indeg[i]){
				gph[a[i]].erase(find(gph[a[i]].begin(), gph[a[i]].end(), i));
			}
		}
		gph[a[1]].erase(find(gph[a[1]].begin(), gph[a[1]].end(), 1));
		pi tmp(-1, -1);
		for(auto &i : dfn){
			if(indeg[i]){
				tmp = max(tmp, pi(dfs1(i).first, i));
			}
		}
		int pos = tmp.second, npos = tmp.second;
		while(a[npos] != pos) npos = a[npos];
		int far = dfs1(1).second;
		a[npos] = far;
		ret++;
		for(int i=1; i<=n; i++){
			gph[i].clear();
		}
		for(int i=1; i<=n; i++){
			gph[a[i]].push_back(i);
		}
	}
	gph[a[1]].erase(find(gph[a[1]].begin(), gph[a[1]].end(), 1));
	path += dfs1(1).first;
	for(int i=1; i<=n; i++){
		if(!vis[i]){
			ret++;
			path += solve(i);
		}
	}
	printf("%d %d\n", ret, path);
}
