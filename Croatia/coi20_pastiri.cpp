// shirley smokes weed
#include <bits/stdc++.h>
#define sz(v) ((lint)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 500005;
const int mod = 998244353;

int n, k;
vector<int> gph[MAXN];
vector<int> fast[MAXN];
vector<int> ord;
bool vis[MAXN];
int dist[MAXN], dep[MAXN], par[MAXN], jump[MAXN];

void bfs(int x){
	vis[x] = 1;
	for(auto &i : fast[x]){
		if(!vis[i]) bfs(i);
	}
}

void dfs(int x, int p = -1){
	for(auto &i : gph[x]){
		if(i != p){
			par[i] = x;
			dep[i] = dep[x] + 1;
			if(dist[i] == dist[x] - 1) jump[i] = jump[x];
			else jump[i] = i;
			dfs(i, x);
		}
	}
	ord.push_back(x);
}

int main(){
	scanf("%d %d",&n,&k);
	for(int i=0; i<n-1; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	memset(dist, 0x3f, sizeof(dist));
	queue<int> que;
	for(int i=0; i<k; i++){
		int x; scanf("%d",&x);
		que.push(x);
		dist[x] = 0;
	}
	while(sz(que)){
		auto x = que.front(); que.pop();
		for(auto &i : gph[x]){
			if(dist[i] > dist[x] + 1){
				dist[i] = dist[x] + 1;
				que.push(i);
			}
		}
	}
	jump[1] = 1;
	dfs(1);
	sort(all(ord), [&](const int &x, const int &y){
		return dep[x] > dep[y];
	});
	for(int i=1; i<=n; i++){
		for(auto &j : gph[i]){
			if(dist[j] == dist[i] - 1) fast[i].push_back(j);
		}
	}
	vector<int> ans;
	for(auto &i : ord){
		if(dist[i] == 0 && !vis[i]){
			int pos = jump[i];
			ans.push_back(pos);
			bfs(pos);
		}
	}
	cout << sz(ans) << endl;
	for(auto &i : ans) printf("%d ", i);
}

