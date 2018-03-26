#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 105;

vector<pi> ed;
int n, p[MAXN], rev[MAXN];

void make_edge(int s, int e){
	ed.push_back(pi(s, e));
}

vector<int> gph[MAXN];
int q[MAXN];
bool vis[MAXN];

void dfs(int x){
	if(vis[x]) return;
	vis[x] = 1;
	for(auto &i : gph[x]){
		dfs(i);
	}
}

bool verify(int prv, int cur){
	for(int i=0; i<MAXN; i++) gph[i].clear();
	memset(vis, 0, sizeof(vis));
	for(auto &i : ed){
		gph[i.first].push_back(i.second);
	}
	dfs(rev[prv]);
	if(vis[rev[cur]]) return true;
	vector<int> l, r;
	for(int i=1; i<cur; i++){
		if(!vis[rev[i]]) l.push_back(rev[i]);
		else r.push_back(rev[i]);
	}
	sort(l.begin(), l.end(), [&](const int &a, const int &b){
		return p[a] < p[b];
	});
	sort(r.begin(), r.end(), [&](const int &a, const int &b){
		return p[a] < p[b];
	});
	int cnt = 0;
	for(auto &i  : l) q[i] = ++cnt;
	q[rev[cur]] = ++cnt;
	for(auto &i : r) q[i] = ++cnt;
	for(int i=1; i<=n; i++){
		if(p[i] > cur) q[i] = p[i];
	}
	printf("query ");
	for(int i=1; i<=n; i++) printf("%d ", q[i]);
	puts("");
	fflush(stdout);
	int x;
	cin >> x;
	return !x;
}

int ans[MAXN];

void dfs2(int x){
	if(vis[x]) return;
	vis[x] = 1;
	for(auto &i : gph[x]) dfs2(i);
}

void dfs(vector<int> v, int s, int e){
	if(v.empty()) return;
	memset(vis, 0, sizeof(vis));
	dfs2(v[0]);
	vector<int> l, r;
	for(auto &j : v){
		if(j == v[0]) continue;
		if(vis[j]) l.push_back(j);
		else r.push_back(j);
	}
	ans[v[0]] = s + l.size();
	dfs(l, s, s + l.size() - 1);
	dfs(r, s + l.size() + 1, e);
}

int main(){
	cin >> n;
	for(int i=1; i<=n; i++){
		cin >> p[i];
		rev[p[i]] = i;
	}
	for(int i=1; i<=n; i++){
		for(int j=i-1; j; j--){
			if(verify(j, i)){
				ed.push_back(pi(rev[j], rev[i]));
			}
		}
	}
	puts("end");
	fflush(stdout);
	vector<int> v;
	for(int i=1; i<=n; i++) v.push_back(i);
	for(int i=0; i<MAXN; i++) gph[i].clear();
	for(auto &i : ed) gph[i.second].push_back(i.first);
	dfs(v, 1, n);
	for(int i=1; i<=n; i++) printf("%d ", ans[i]);
	puts("");
	for(int i=0; i<MAXN; i++) gph[i].clear(), ans[i] = 0;
	for(auto &i : ed) gph[i.first].push_back(i.second);
	dfs(v, 1, n);
	for(int i=1; i<=n; i++) printf("%d ", n+1-ans[i]);
}
