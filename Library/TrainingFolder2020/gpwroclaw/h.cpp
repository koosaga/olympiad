#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const int MAXN = 500005;
const int MAXM = 500005;

static char buf[1 << 19]; // size : any number geq than 1024
static int idx = 0;
static int bytes = 0;
static inline int _read() {
	if (!bytes || idx == bytes) {
		bytes = (int)fread(buf, sizeof(buf[0]), sizeof(buf), stdin);
		idx = 0;
	}
	return buf[idx++];
}
static inline int _readInt() {
	int x = 0, s = 1;
	int c = _read();
	while (c <= 32) c = _read();
	if (c == '-') s = -1, c = _read();
	while (c > 32) x = 10 * x + (c - '0'), c = _read();
	if (s < 0) x = -x;
	return x;
}


int n, m, s[MAXM], e[MAXM];
vector<int> gph[MAXN];
vector<int> dag[MAXN];
vector<int> cyc;
vector<int> tsort;
int in_cyc[MAXN], indeg[MAXN], par[MAXN], instk[MAXN], vis[MAXN];

void clear(){
	for(int i=0; i<=max(n, m); i++){
		indeg[i] = par[i] = instk[i] = vis[i] = 0;
		gph[i].clear();
		dag[i].clear();
	}
	cyc.clear();
	tsort.clear();
}

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

int mian(){
	n = _readInt();
	m = _readInt();
	for(int i=0; i<m; i++){
		s[i] = _readInt();
		e[i] = _readInt();
		gph[s[i]].push_back(e[i]);
	}
	for(int i=1; i<=n; i++){
		if(cyc.size()) break;
		if(!vis[i]) dfs1(i);
	}
	if(cyc.empty()){
		printf("%d ", n);
		for(int i=1; i<=n; i++) printf("%d ", i);
		puts("");
		return 0;
	}
	for(int i=1; i<=n; i++) in_cyc[i] = -1;
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
	vector<int> dp1(n + 1, -1e9);
	vector<int> dp2(n + 1, 1e9);
	vector<int> dp3(n + 1, -1e9);
	vector<int> dx(n + 1, 0);
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
	printf("%d ", ans.size());
	for(auto &i : ans) printf("%d ", i);
	puts("");
	return 0;
}

int main(){
	int tc = _readInt();
	while(tc--){
		mian();
		clear();
	}
}
