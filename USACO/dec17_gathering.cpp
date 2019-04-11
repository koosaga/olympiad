#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 100005;

int n, m;
pi a[MAXN];
vector<int> gph[MAXN];
vector<int> aug[MAXN];
int chk[MAXN], din[MAXN], dout[MAXN], piv;
int instk[MAXN], vis[MAXN], dx[MAXN], bad;

void dfs2(int x){
	if(instk[x]){
		bad = 1;
		return;
	}
	if(vis[x]) return;
	instk[x] = 1;
	vis[x] = 1;
	for(auto &i : aug[x]){
		dfs2(i);
	}
	instk[x] = 0;
}

void dfs(int x, int p){
	din[x] = ++piv;
	for(auto &i : gph[x]){
		if(i != p){
			gph[i].erase(find(gph[i].begin(), gph[i].end(), x));
			dfs(i, x);
		}
	}
	dout[x] = piv;
}

bool sub(int x, int y){
	return din[x] <= din[y] && dout[y] <= dout[x];
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n-1; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, -1);
	for(int i=0; i<m; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
		aug[a[i].second].push_back(a[i].first);
		if(!sub(a[i].first, a[i].second)){
			dx[din[a[i].first]]++;
			dx[dout[a[i].first] + 1]--;
		}
		else{
			dx[1]++;
			dx[n+1]--;
			int nxt = *--upper_bound(gph[a[i].first].begin(), gph[a[i].first].end(), a[i].second, 
			[&](const int &a, const int &b){
				return din[a] < din[b];
			});
			dx[din[nxt]]--;
			dx[dout[nxt]+1]++;
		}
	}
	for(int i=1; i<=n; i++){
		if(!vis[i]){
			dfs2(i);
			if(bad){
				for(int j=1; j<=n; j++) puts("0");
				return 0;
			}
		}
	}
	for(int i=1; i<=n; i++) dx[i] += dx[i-1];
	for(int i=1; i<=n; i++){
		if(dx[din[i]]) puts("0");
		else puts("1");
	}
}
