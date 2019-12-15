#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = __int128;
using pi = pair<lint, lint>;
const int MAXN = 100005;
const int mod = 1e9 + 7;

int n;
// qry[i] : (where does it leads to, for what cost)
// nxt[i] : (where does it leads to, for what addition)
// val[i] : what HP to take qry[i]
// result[i] : (how long, where (as a portal) does it leads to)

pi qry[MAXN], nxt[MAXN];
vector<pi> revlist[MAXN];
pi result[MAXN];
lint val[MAXN];
bool visited[MAXN];

namespace FindEnd{
	vector<int> gph[MAXN];
	map<lint, int> mp;
	int dep[MAXN];
	void dfs(int x, lint depth){
		visited[x] = 1;
		int restore = -1;
		if(x <= n){
			if(mp.count(val[x] + depth)){
				restore = mp[val[x] + depth];
			}
			mp[val[x] + depth] = x;
		}
		for(auto &fuck : revlist[x]){
			auto i = fuck.first;
			auto j = fuck.second;
			if(mp.count(i + depth)){
				int vert = mp[i + depth];
				result[j] = pi(dep[x] - dep[vert], vert);
			}
			else{
				result[j] = pi(dep[x], n + 1);
			}
		}
		for(auto &i : gph[x]){
			dep[i] = dep[x] + 1;
			dfs(i, depth + nxt[i].second);
		}
		if(x <= n){
			if(~restore) mp[val[x] + depth] = restore;
			else mp.erase(mp.find(val[x] + depth));
		}
	}
	void solve(){
		for(int i=1; i<=n; i++){
			gph[nxt[i].first].push_back(i);
		}
		dfs(n + 1, 0);
	}
}

namespace MatchQuery{
	int indeg[MAXN], dep[MAXN];
	vector<int> gph[MAXN];
	map<lint, int> mp;
	void dfs(int x, lint depth, vector<pi> &collected){
		int restore = -1;
		if(mp.count(val[x] + depth)){
			restore = mp[val[x] + depth];
		}
		mp[val[x] + depth] = x;
		for(auto &fuck : revlist[x]){
			auto i = fuck.first;
			auto j = fuck.second;
			if(mp.count(i + depth)){
				int vert = mp[i + depth];
				result[j] = pi(dep[x] - dep[vert], vert);
			}
			else{
				collected.emplace_back(i + depth, j);
			}
		}
		for(auto &i : gph[x]){
			if(indeg[i]) continue;
			dep[i] = dep[x] + 1;
			dfs(i, depth + nxt[i].second, collected);
		}
		if(~restore) mp[val[x] + depth] = restore;
		else mp.erase(mp.find(val[x] + depth));
	}
	void solve(){
		vector<int> noe;
		for(int i=1; i<=n; i++){
			if(visited[i]) continue;
			noe.push_back(i);
		}
		for(auto &i : noe){
			indeg[nxt[i].first]++;
			gph[nxt[i].first].push_back(i);
		}
		queue<int> que;
		for(auto &i : noe){
			if(!indeg[i]){
				que.push(i);
			}
		}
		while(sz(que)){
			int x = que.front(); que.pop();
			indeg[nxt[x].first]--;
			if(indeg[nxt[x].first] == 0) que.push(nxt[x].first);
		}
		for(auto &i : noe){
			if(!indeg[i]) continue;
			vector<int> v = {i};
			vector<vector<pi>> w;
			lint T = nxt[i].second;
			for(int j = nxt[i].first; j != i; j= nxt[j].first){
				v.push_back(j);
				T += nxt[j].second;
			}
			for(auto &i : v){
				vector<pi> ww;
				dfs(i, 0, ww);
				w.push_back(ww);
			}
			if(T < 0){
				for(auto &j : v){
					nxt[j].second *= -1;
					val[j] *= -1;
				}
				for(auto &j : w){
					for(auto &k : j){
						k.first *= -1;
					}
				}
				T *= -1;
			}
			if(T == 0) T = 696969420420420420ll;
			auto D = [&](lint x){
				if(x >= 0) return x / T;
				return (x - T + 1) / T;
			};
			for(auto &i : v) indeg[i] = 0;
			vector<lint> psum(2 * sz(v) + 1);
			for(int i=0; i<sz(v); i++){
				psum[i + 1] = nxt[v[i]].second;
				psum[i + 1 +sz(v)] = nxt[v[i]].second;
			}
			for(int i=1; i<sz(psum); i++) psum[i] += psum[i-1];
			set<tuple<lint, lint, lint>> s;
			vector<tuple<lint, lint, lint>> lis(2 * sz(v));
			for(int i=0; i<2*sz(v); i++){
				lint key = val[v[i%sz(v)]] - psum[i];
				lis[i] = make_tuple(key - D(key) * T, key, (lint)i);
			}
			for(int i=0; i<sz(v); i++) s.insert(lis[i]);
			for(int i=0; i<sz(v); i++){
				for(auto fuck : w[i]){
					auto k = fuck.first;
					auto l = fuck.second;
					lint curk = k - psum[i];
					auto lbnd = s.lower_bound(make_tuple(curk - D(curk) * T, curk, (lint)-1));
					if(lbnd != s.end() && get<0>(*lbnd) == curk - D(curk) * T){
						lint nxtk = get<1>(*lbnd);
						int dist = get<2>(*lbnd) + dep[qry[l].first] - i;
						int vtx = v[get<2>(*lbnd) % sz(v)];
						lint ndist = dist + ((nxtk - curk) / T) * sz(v);
						result[l] = min(result[l], pi(ndist, vtx));
					}
				}
				s.erase(lis[i]);
				s.insert(lis[i + sz(v)]);
			}
		}
	}
}

int main(){
	long long ff;
	scanf("%d %lld",&n,&ff);
	qry[0].first = 1;
	qry[0].second = ff;
	for(int i=1; i<=n; i++){
		long long a, b, c, d, e;
		scanf("%lld %lld %lld %lld %lld",&a,&b,&c,&d,&e);
		qry[i] = pi(c, a + b);
		nxt[i] = pi(e, d);
		val[i] = a;
	}
	nxt[n + 1] = pi(n + 1, n + 1);
	fill(result, result + n + 1, pi((lint)1e30, -1));
	for(int i=0; i<=n; i++){
		revlist[qry[i].first].emplace_back(qry[i].second, i);
	}
	FindEnd::solve();
	MatchQuery::solve();
	int pos = 0;
	lint ret = 0;
	vector<int> vis(n + 2);
	while(pos != n + 1 && !vis[pos]){
		vis[pos] = 1;
		ret += result[pos].first;
		ret %= mod;
		pos = result[pos].second;
		if(pos == -1) break;
		if(pos == n + 1) break;
		ret++;
		ret %= mod;
	}
	if(pos != n + 1) puts("-1");
	else cout << (int)(ret % mod) << endl;
}



