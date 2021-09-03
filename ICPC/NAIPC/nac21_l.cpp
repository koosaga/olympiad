#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 998244353;

int n, m, d;
vector<lint> v;
vector<pi> gph[MAXN];
int dp[MAXN];
lint dist[MAXN];

int main(){
	scanf("%d %d %d",&n,&m,&d);
	for(int i = 0; i < m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		gph[s].emplace_back(x, e);
	}
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	memset(dist, 0x3f, sizeof(dist));
	auto enq = [&](int x, lint d){
		if(dist[x] > d){
			dist[x] = d;
			pq.emplace(d, x);
		}
	};
	enq(1, 0);
	vector<int> ord;
	while(sz(pq)){
		auto x = pq.top(); pq.pop();
		if(dist[x.second] != x.first) continue;
		ord.push_back(x.second);
		for(auto &[w, v] : gph[x.second]){
			enq(v, w + x.first);
		}
	}
	vector<lint> vect;
	for(int i = 0; i < d; i++){
		lint q; scanf("%lld",&q);
		if(dist[n] < q){
			puts("0");
			return 0;
		}
		vect.push_back(q);
	}
	sort(all(vect));
	reverse(all(ord));
	for(auto &u : ord){
		if(u == n) dp[u] = 1;
		else{
			for(auto &[w, v] : gph[u]){
				if(dist[v] != dist[u] + w) continue;
				int cnt = lower_bound(all(vect), dist[v]) - lower_bound(all(vect), dist[u] + 1);
				if(cnt == 0) dp[u] += dp[v];
			}
		}
		dp[u] = min(dp[u], 69);
	}
	if(dp[1] == 0){
		puts("0");
		return 0;
	}
	if(dp[1] > 1){
		puts("1");
		return 0;
	}
	int pos = 1;
	vector<int> ans;
	while(pos != n){
		ans.push_back(pos);
		for(auto &[w, v] : gph[pos]){
			if(dist[v] == dist[pos] + w && dp[v]){
				pos = v;
				break;
			}
		}
	}
	ans.push_back(n);
	printf("%d\n", sz(ans));
	for(auto &i : ans) printf("%d\n", i);
}

