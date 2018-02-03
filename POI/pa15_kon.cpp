#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const int MAXN = 500005;
const int MAXM = 1000005;

int n, m, s[MAXM], e[MAXM];
vector<int> gph[MAXN];
vector<int> dag[MAXN];
vector<int> cyc;
vector<int> tsort;
int in_cyc[MAXN], indeg[MAXN], par[MAXN], instk[MAXN], vis[MAXN];
int dp1[MAXN], dp2[MAXN], dp3[MAXN], dx[MAXN];

void dfs1(int x){
	if(!cyc.empty()) return;
	if(instk[x]){
		cyc.push_back(x);
		do{
			cyc.push_back(par[cyc.back()]);
		}while(cyc.back() != x);
		reverse(cyc.begin(), cyc.end());
		cyc.pop_back();
		return;
	}
	if(vis[x]) return;
	instk[x] = 1;
	vis[x] = 1;
	for(auto &i : gph[x]){
		par[i] = x;
		dfs1(i);
	}
	instk[x] = 0;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		scanf("%d %d",&s[i],&e[i]);
		gph[s[i]].push_back(e[i]);
	}
	for(int i=1; i<=n; i++){
		if(cyc.size()) break;
		if(!vis[i]) dfs1(i);
	}
	if(cyc.empty()){
		puts("NIE");
		return 0;
	}
	memset(in_cyc, -1, sizeof(in_cyc));
	for(int i=0; i<cyc.size(); i++) in_cyc[cyc[i]] = i; // printf("%d ", cyc[i]);
	for(int i=0; i<m; i++){
		if(in_cyc[s[i]] == -1 && in_cyc[e[i]] == -1){
			dag[s[i]].push_back(e[i]);
			indeg[e[i]]++;
		}
		if(in_cyc[s[i]] == -1 && in_cyc[e[i]] != -1){
			dag[e[i]].push_back(s[i]);
		}
	}
	queue<int> que;
	for(int i=1; i<=n; i++){
		if(in_cyc[i] == -1 && indeg[i] == 0){
			que.push(i);
		}
	}
	while(!que.empty()){
		int x = que.front();
		tsort.push_back(x);
		que.pop();
		for(auto &i : dag[x]){
			indeg[i]--;
			if(indeg[i] == 0){
				que.push(i);
			}
		}
	}
	for(int i=1; i<=n; i++){
		if(indeg[i]){
			puts("0");
			return 0;
		}
	}
	fill(dp1, dp1 + n + 1, -1e9);
	fill(dp2, dp2 + n + 1, 1e9);
	fill(dp3, dp3 + n + 1, -1e9);
	for(int i=0; i<m; i++){
		if(in_cyc[s[i]] == -1 && in_cyc[e[i]] == -1) continue;
		if(in_cyc[s[i]] != -1 && in_cyc[e[i]] == -1){
			dp3[e[i]] = max(dp3[e[i]], in_cyc[s[i]]);
		}
		if(in_cyc[s[i]] == -1 && in_cyc[e[i]] != -1){
			dp1[s[i]] = max(dp1[s[i]], in_cyc[e[i]]);
			dp2[s[i]] = min(dp2[s[i]], in_cyc[e[i]]);
		}
		if(in_cyc[s[i]] != -1 && in_cyc[e[i]] != -1){
			if(in_cyc[s[i]] < in_cyc[e[i]]){
				dx[in_cyc[s[i]] + 1]++;
				dx[in_cyc[e[i]]]--;
			}
			else{
				dx[in_cyc[s[i]] + 1]++;
				dx[cyc.size()]--;
				dx[0]++;
				dx[in_cyc[e[i]]]--;
			}
		}
	}
	for(int i=tsort.size()-1; i>=0; i--){
		for(auto &j : dag[tsort[i]]){
			dp1[tsort[i]] = max(dp1[tsort[i]], dp1[j]);
			dp2[tsort[i]] = min(dp2[tsort[i]], dp2[j]);
		}
	}
	for(int i=0; i<tsort.size(); i++){
		for(auto &j : dag[tsort[i]]){
			dp3[j] = max(dp3[j], dp3[tsort[i]]);
		}
	}
	for(int i=0; i<cyc.size(); i++){
		int mxv = 0, mnv = 1e9;
		int case3 = -1e9;
		for(auto &j : gph[cyc[i]]){
			if(in_cyc[j] == -1){
				mxv = max(mxv, dp1[j]);
				mnv = min(mnv, dp2[j]);
			}
		}
		for(auto &j : dag[cyc[i]]){
			case3 = max(case3, dp3[j]);
		}
		if(i+1 <= mxv){
			dx[i+1]++;
			dx[mxv]--;
		}
		if(i >= mnv){
			dx[i+1]++;
			dx[cyc.size()]--;
		}
		if(i <= case3){
			dx[0]++;
			dx[i]--;
		}
	}
	for(int i=1; i<=cyc.size(); i++) dx[i] += dx[i-1];
	vector<int> ans;
	for(int i=0; i<cyc.size(); i++){
		if(dx[i] == 0){
			ans.push_back(cyc[i]);
		}
	}
	sort(ans.begin(), ans.end());
	printf("%d\n", ans.size());
	for(auto &i : ans) printf("%d ", i);
}

