#include <bits/stdc++.h>
typedef long long lint;
using namespace std;
typedef pair<int, int>pi;
const int MAXN = 200005;

int n, m, k;
vector<int> gph[MAXN];
int deg[MAXN], vis[MAXN], ptr[MAXN];
int enxt[MAXN], eprv[MAXN];
pi edg[MAXN];

vector<int> ans;

void dfs(int x){
	vis[x] = 1;
	if(enxt[x] != -1){
		if(vis[enxt[x]]){
			return;
		}
		dfs(enxt[x]);
	}
	else{
		int nxt = edg[x].second;
		while(ptr[nxt] < gph[nxt].size()){
			if(vis[gph[nxt][ptr[nxt]]] || eprv[gph[nxt][ptr[nxt]]] != -1){
				ptr[nxt]++;
				continue;
			}
			int edg = gph[nxt][ptr[nxt]];
			ptr[nxt]++;
			dfs(edg);
		}
	}
	ans.push_back(x);
}

int main(){
	memset(eprv, -1, sizeof(eprv));
	memset(enxt, -1, sizeof(enxt));
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		edg[i] = pi(x, y);
		deg[x]++;
		deg[y]--;
	}
	if(count(deg + 1, deg + n + 1, 0) != n){
		puts("NIE");
		return 0;
	}
	sort(edg, edg + m);
	for(int i=0; i<m; i++){
		gph[edg[i].first].push_back(i);
	}
	scanf("%d",&k);
	for(int i=1; i<=k; i++){
		int x;
		scanf("%d",&x);
		vector<int> w(x), v;
		for(auto &j : w) scanf("%d",&j);
		for(int j=1; j<w.size(); j++){
			int l = lower_bound(edg, edg + m, pi(w[j-1], w[j])) - edg;
			if(l == m || edg[l] != pi(w[j-1], w[j])){
				puts("NIE");
				return 0;
			}
			v.push_back(l);
		}
		for(int i=0; i+1<v.size(); i++){
			if(enxt[v[i]] != -1 && enxt[v[i]] != v[i+1]){
				puts("NIE");
				return 0;
			}
			if(eprv[v[i+1]] != -1 && eprv[v[i+1]] != v[i]){
				puts("NIE");
				return 0;
			}
			enxt[v[i]] = v[i+1];
			eprv[v[i+1]] = v[i];
		}
	}
	for(auto &i : gph[1]){
		if(eprv[i] != -1 || vis[i]) continue;
		dfs(i);
	}
	if(ans.size() != m){
		puts("NIE");
		return 0;
	}
	reverse(ans.begin(), ans.end());
	puts("TAK");
	for(auto &i : ans) printf("%d\n", edg[i].first);
	puts("1");
}

