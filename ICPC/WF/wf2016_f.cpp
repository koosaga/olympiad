#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
const int MAXN = 1000005;
using lint = long long;
using pi = pair<lint, int>;

int n, m, ans[MAXN];
vector<pi> gph[MAXN];
char str[MAXN][15];
lint dep[MAXN], minv[MAXN], maxv[MAXN];
int par[MAXN], pae[MAXN];

void dfs(int x){
	if(sz(gph[x])) minv[x] = 1e18;
	for(auto &i : gph[x]){
		dep[i.second] = i.first + dep[x];
		par[i.second] = x;
		pae[i.second] = i.first;
		dfs(i.second);
		minv[x] = min(minv[i.second] + i.first, minv[x]);
		maxv[x] = max({maxv[i.second], minv[i.second] + i.first, maxv[x]});
	}
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		int x, y; scanf("%s %d %d",str[i],&x,&y);
		gph[x].emplace_back(y, i + m);
	}
	for(int i=1; i<=m; i++){
		int x, y; scanf("%d %d",&x,&y);
		gph[x].emplace_back(y, i);
	}
	dfs(0);
	vector<pi> swp, evnt;
	priority_queue<lint, vector<lint>, greater<lint>> cnt;
	for(int i=m+1; i<=m+n; i++) swp.emplace_back(dep[i], i - m);
	for(int i=1; i<=m+n; i++) evnt.emplace_back(maxv[i], i);
	sort(swp.begin(), swp.end());
	sort(evnt.begin(), evnt.end());
	int p = 0;
	for(auto &i : swp){
		while(p < sz(evnt) && evnt[p].first <= i.first){
			int j = evnt[p++].second;
			cnt.push(minv[j] + pae[j]);
		}
		while(sz(cnt) && cnt.top() <= i.first) cnt.pop();
		ans[i.second] = sz(cnt) + 1;
	}
	for(int i=1; i<=n; i++){
		printf("%s %d\n", str[i], ans[i]);
	}
}
