#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
typedef priority_queue<pi, vector<pi>, greater<pi> > pque;

int n;
lint c[200005];
vector<int> gph[200005];

pque dfs(int x, int p){
	pque pq;
	for(auto &i : gph[x]){
		if(i == p) continue;
		auto t = dfs(i, x);
		if(t.size() > pq.size()) swap(t, pq);
		while(!t.empty()){
			pq.push(t.top());
			t.pop();
		}
	}
	pi t = pi(max(-c[x], 0ll), max(c[x], 0ll));
	while(!pq.empty() && (t.second <= t.first || t.second >= pq.top().first)){
		auto x = pq.top();
		lint tmp = t.second - t.first + x.second - x.first;
		t.first = max(t.first, t.first - t.second + x.first);
		t.second = tmp + t.first;
		pq.pop();
	}
	if(t.first < t.second) pq.push(t);
	return pq;
}

void solve(){
	int x;
	scanf("%d %d",&n,&x);
	gph[x].push_back(n+1);
	gph[n+1].push_back(x);
	c[n+1] = 2e15;
	for(int i=1; i<=n; i++){
		scanf("%lld",&c[i]);
	}
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	auto ret = dfs(1, 0);
	lint curhel = 0;
	while(!ret.empty()){
		auto t = ret.top();
		ret.pop();
		if(curhel < t.first) break;
		curhel += t.second - t.first;
	}
	if(curhel > 1e15) puts("escaped");
	else puts("trapped");
}

int main(){
	int t;
	cin >>t;
	while(t--){
		solve();
		for(int i=1; i<=n+1; i++){
			gph[i].clear();
		}
	}
}
