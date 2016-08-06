#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, q, k;
vector<pi> gph[100005];
int s[100005], e[100005];

int cnt[100005], lst[100005], chk[100005];

int grp[100005], grpcnt[100005], piv;
vector<pi> cgph[100005];

void dfs1(int x, int p){
	grp[x] = piv;
	for(auto &i : gph[x]){
		if(i.second == p) continue;
		if(chk[i.first]) continue;
		dfs1(i.second, x);
	}
}

void dfs2(int x, int p, int v){
	grpcnt[x] = v;
	for(auto &i : cgph[x]){
		if(i.second == p) continue;
		if(chk[i.first]) continue;
		dfs2(i.second, x, v);
	}
}

bool vis[100005];
void solve(vector<int> v){
	for(auto &i : v){
		chk[i]++;
	}
	for(int i=1; i<=n; i++){
		if(!grp[i]){
			piv++;
			grpcnt[piv] = cnt[i];
			dfs1(i, -1);
		}
	}
	for(auto &i : v){
		chk[i]--;
		vis[grp[s[i]]] = vis[grp[e[i]]] = 1;
	}
	for(int i=1; i<n; i++){
		if(grp[s[i]] != grp[e[i]] && vis[grp[s[i]]] && vis[grp[e[i]]]){
			cgph[grp[s[i]]].push_back(pi(i, grp[e[i]]));
			cgph[grp[e[i]]].push_back(pi(i, grp[s[i]]));
		}
	}
	for(auto &i : v){
		if(!chk[i]){
			chk[i] = 1;
			lst[i] = grpcnt[grp[s[i]]];
		}
		else{
			chk[i] = 0; // set value
			dfs2(grp[s[i]], -1, grpcnt[grp[s[i]]] + grpcnt[grp[e[i]]] - lst[i]);
		}
	}
	for(int i=1; i<=n; i++){
		cnt[i] = grpcnt[grp[i]];
	}
	for(int i=1; i<=piv; i++){
		cgph[i].clear();
	}
	piv = 0;
	memset(grp, 0, sizeof(grp));
	memset(vis, 0, sizeof(vis));
}

int main(){
	scanf("%d %d %d",&n,&q,&k);
	for(int i=1; i<n; i++){
		scanf("%d %d",&s[i],&e[i]);
		gph[s[i]].push_back({i, e[i]});
		gph[e[i]].push_back({i, s[i]});
	}
	for(int i=1; i<n; i++){
		chk[i] = 1;
	}
	for(int i=1; i<=n; i++){
		cnt[i]++;
	}
	vector<int> stk;
	for(int i=0; i<q; i++){
		int x;
		scanf("%d",&x);
		stk.push_back(x);
		if(stk.size() >= 1000){
			solve(stk);
			stk.clear();
		}
	}
	if(!stk.empty()) solve(stk);
	for(int i=0; i<k; i++){
		int x;
		scanf("%d",&x);
		printf("%d\n", cnt[x]);
	}
}