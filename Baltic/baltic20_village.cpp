#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const int MAXN = 500005;

int n;
vector<int> gph[MAXN];
int dp[MAXN], sum[MAXN], par[MAXN], trace[MAXN];
vector<int> dfn;

void dfsw(int x, int p = -1){
	dfn.push_back(x);
	for(auto &i : gph[x]){
		if(i != p){
			par[i] = x;
			dfsw(i, x);
		}
	}
}

bool chk[MAXN];
vector<int> v[MAXN];

pair<lint, vector<int>> solve_small(){
	dfsw(1);
	reverse(all(dfn));
	for(auto &i : dfn){
		pi kappa(0, -1);
		for(auto &j : gph[i]){
			if(j == par[i]) continue;
			sum[i] += dp[j];
			dp[i] += dp[j];
			kappa = max(kappa, pi(sum[j] - dp[j] + 1, j));
		}
		if(kappa.first > 0){
			dp[i] += kappa.first;
			trace[i] = kappa.second;
		}
	}
	reverse(all(dfn));
	for(auto &i : dfn){
		if(chk[i]) continue;
		if(trace[i]){
			v[i].push_back(i);
			chk[i] = chk[trace[i]] = 1;
		}
	}
	for(int i=1; i<=n; i++){
		if(!trace[i]){
			if(chk[i]) v[par[i]].push_back(i);
			else{
				for(auto &j : gph[i]){
					if(chk[j]){
						v[j].push_back(i);
						break;
					}
				}
			}
		}
	}
	vector<int> p(n);
	for(int i=1; i<=n; i++){
		for(int j=0; j<sz(v[i]); j++){
			p[v[i][j] - 1] = v[i][(j + 1) % sz(v[i])] - 1;
		}
	}
	return make_pair(2ll*n-2*dp[1], p);
}

vector<pi> lists[MAXN];
int sz[MAXN], msz[MAXN];

void dfsz(int x, int p = -1){
	sz[x] = 1; msz[x] = 0;
	for(auto &i : gph[x]){
		if(i != p){
			dfsz(i, x);
			sz[x] += sz[i];
			msz[x] = max(msz[x], sz[i]);
		}
	}
}

int get_center(){
	dfsz(1);
	pi ret(1e9, 1e9);
	for(int i=1; i<=n; i++){
		int foo = max(n - sz[i], msz[i]);
		ret = min(ret, pi(foo, i));
	}
	return ret.second;
}

void dfs(int x, int p, int t, int d){
	lists[t].emplace_back(d, x);
	for(auto &i : gph[x]){
		if(i != p){
			dfs(i, x, t, d + 1);
		}
	}
}

pair<lint, vector<int>> solve_large(){
	int c = get_center();
	lists[c].emplace_back(0, c);
	lint ret = 0;
	priority_queue<pi> pq;
	for(auto &v : gph[c]){
		dfs(v, c, v, 1);
		sort(all(lists[v]));
		for(auto &w : lists[v]) ret += 2 * w.first;
		pq.emplace(sz(lists[v]), v);
	}
	if(n % 2 == 0) pq.emplace(sz(lists[c]), c);
	vector<int> p(n);
	for(int i=0; i<n/2; i++){
		auto t1 = pq.top(); pq.pop();
		auto t2 = pq.top(); pq.pop();
		int v1 = lists[t1.second].back().second;
		int v2 = lists[t2.second].back().second;
		lists[t1.second].pop_back();
		lists[t2.second].pop_back();
		if(i == n / 2 - 1 && n % 2 == 1){
			p[v1 - 1] = c - 1;
			p[v2 - 1] = v1 - 1;
			p[c - 1] = v2 - 1;
			break;
		}
		p[v1 - 1] = v2 - 1;
		p[v2 - 1] = v1 - 1;
		if(t1.first>1) pq.emplace(t1.first - 1, t1.second);
		if(t2.first>1) pq.emplace(t2.first - 1, t2.second);
	}
	return make_pair(ret, p);
}

int main(){
	scanf("%d",&n);
	assert(n >= 2);
	for(int i=1; i<n; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	lint s1, s2;
	vector<int> p1, p2;
	tie(s1, p1) = solve_small();
	tie(s2, p2) = solve_large();
	printf("%lld %lld\n", s1, s2);
	for(auto &i : p1) printf("%d ", i + 1); puts("");
	for(auto &i : p2) printf("%d ", i + 1); puts("");
}
