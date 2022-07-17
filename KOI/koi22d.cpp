#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 200005;

struct query{
	int s, e, idx;
	bool operator<(const query &q)const{
		return s < q.s;
	}
};

vector<pi> gph[MAXN];
vector<int> tr[MAXN];

vector<int> dfn;
int label[MAXN], vis[MAXN];
int sz[MAXN], msz[MAXN];

lint ans[250005];

void dfs(int x, int p){
	dfn.push_back(x);
	sz[x] = 1; msz[x] = 0;
	for(auto &y : tr[x]){
		if(y != p && !vis[y]){
			dfs(y, x);
			sz[x] += sz[y];
			msz[x] = max(msz[x], sz[y]);
		}
	}
}
int get_center(int x){
	dfs(x, -1);
	pi ret(1e9, -1);
	for(auto &v : dfn){
		int val = max(msz[v], sz(dfn) - sz[v]);
		ret = min(ret, pi(val, v));
	}
	return ret.second;
}

void fill_label(int x, int p, int v){
	label[x] = v;
	for(auto &y : tr[x]){
		if(y != p && !vis[y]) fill_label(y, x, v);
	}
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int n; cin >> n;
	{
		vector<int> pidx(n + 1); iota(all(pidx), 0);
		vector<int> needClean(n + 1);
		int cnt = n;
		for(int i = 2; i <= n; i++){
			lint p, w; cin >> p >> w;
			if(needClean[p]){
				cnt++;
				gph[cnt].emplace_back(0, pidx[p]);
				gph[pidx[p]].emplace_back(0, cnt);
				tr[pidx[p]].push_back(cnt);
				tr[cnt].push_back(pidx[p]);
				pidx[p] = cnt;
				needClean[p] = 0;
			}
			gph[pidx[p]].emplace_back(w, i);
			gph[i].emplace_back(w, pidx[p]);
			tr[pidx[p]].push_back(i);
			tr[i].push_back(pidx[p]);
			needClean[p] = 1;
		}
		vector<int> v;
		for(int i = 1; i <= n; i++){
			if(sz(gph[i]) == 1) v.push_back(i);
		}
		for(int i = 0; i < sz(v); i++){
			int x = v[i], y = v[(i + 1) % sz(v)];
			lint w; cin >> w;
			gph[x].emplace_back(w, y);
			gph[y].emplace_back(w, x);
		}
		n = cnt;
	}
	int q; cin >> q;
	vector<query> queries;
	memset(ans, 0x3f, sizeof(ans));
	for(int i = 0; i < q; i++){
		int s, e; cin >> s >> e;
		queries.push_back({s, e, i});
	}
	queue<pair<int, vector<query>>> que;
	que.emplace(1, queries);
	vector<lint> dist(n + 1, 1e18);
	while(sz(que)){
		int x = que.front().first;
		auto queries = que.front().second;
		que.pop();
		dfn.clear();
		x = get_center(x);
		int cnt = 0;
		for(auto &y : tr[x]){
			if(!vis[y]){
				fill_label(y, x, ++cnt);
			}
		}
		label[x] = -1;
		vector<int> todo = {x}; 
		for(auto &v : dfn){
			for(auto &[_, w] : gph[v]){
				if(label[v] > 0 && label[w] > 0 && label[v] < label[w]){
					todo.push_back(v);
				}
			}
		}
		assert(sz(todo) <= 4);
		for(auto &v : todo){
			for(auto &w : dfn) dist[w] = 1e18;
			priority_queue<pi, vector<pi>, greater<pi> > pq;
			auto enq = [&](int x, lint v){
				if(label[x] && dist[x] > v){
					dist[x] = v;
					pq.emplace(v, x);
				}
			};
			enq(v, 0);
			while(sz(pq)){
				auto x = pq.top(); pq.pop();
				if(dist[x.second] != x.first) continue;
				for(auto &y : gph[x.second]){
					enq(y.second, y.first + x.first);
				}
			}
			for(auto &q : queries){
				ans[q.idx] = min(ans[q.idx], dist[q.s] + dist[q.e]);
			}
		}
		vector<vector<query>> vect(cnt);
		for(auto &q : queries){
			if(label[q.s] <= 0 || label[q.e] <= 0 || label[q.s] != label[q.e]) continue;
			vect[label[q.s] - 1].push_back(q);
		}
		vis[x] = 1;
		int tcnt = 0;
		for(auto &y : tr[x]){
			if(!vis[y]){
				que.emplace(y, vect[tcnt++]);
			}
		}
		for(auto &z : dfn){
			label[z] = 0;
		}
	}
	for(int i = 0; i < q; i++) cout << ans[i] << "\n";
}


