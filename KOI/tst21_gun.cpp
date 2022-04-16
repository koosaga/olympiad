#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXT = 270000;
const int MAXN = 1 << 17;

struct seg{
	int tree[MAXN];
	void init(int n){
		fill(tree, tree + MAXN, -1e9);
	}
	void upd(int x, int v){
		for(int i = x; i < MAXN; i += i & -i){
			tree[i] = max(tree[i], v);
		}
	}
	int query(int x){
		int ret = -1e9;
		for(int i = x; i > 0; i -= i & -i){
			ret = max(ret, tree[i]);
		}
		return ret;
	}
}seg;

struct seg2{
	pi tree[MAXT];
	int lim;
	void init(int n){
		fill(tree, tree + MAXT, pi(-1e9, -1e9));
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void upd(int x, pi v){
		x += lim;
		tree[x] = v;
		while(x > 1){
			x >>= 1;
			tree[x] = max(tree[2*x], tree[2*x+1]);
		}
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(-1e9, -1e9);
		while(s < e){
			if(s%2 == 1) ret = max(ret, tree[s++]);
			if(e%2 == 0) ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = max(ret, tree[s]);
		return ret;
	}
}seg2;

struct seg2d{
	vector<pi> tree[MAXT];
	int lim;
	void init(vector<pi> v){
		for(lim = 1; lim <= sz(v); lim <<= 1);
		sort(all(v), [&](pi &a, pi &b){
				return a.second < b.second;
				});
		for(int i = 0; i < MAXT; i++) tree[i].emplace_back(0, 0);
		for(auto &[x, y] : v){
			for(int j = x + lim; j; j >>= 1){
				tree[j].emplace_back(y, 0);
			}
		}
	}
	void add(int x, int y, int v){
		auto upd = [&](int n, int m, int v){
			int pos = lower_bound(all(tree[n]), pi(m, -1)) - tree[n].begin();
			for(int i = pos; i < sz(tree[n]); i += i & -i){
				tree[n][i].second = max(tree[n][i].second, v);
			}
		};
		for(int i = x + lim; i; i >>= 1){
			upd(i, y, v);
		}
	}
	int query(int s, int e, int x){
		auto qnode = [&](int v, int x){
			int pos = lower_bound(all(tree[v]), pi(x + 1, -1)) - tree[v].begin() - 1;
			int ret = 0;
			while(pos){
				ret = max(ret, tree[v][pos].second);
				pos -= pos & -pos;
			}
			return ret;
		};
		s += lim;
		e += lim;
		int ret = 0;
		while(s < e){
			if(s%2 == 1) ret = max(ret, qnode(s++, x));
			if(e%2 == 0) ret = max(ret, qnode(e--, x));
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = max(ret, qnode(s, x));
		return ret;
	}
}segx, segy;

vector<pair<int, int>> min_shooting_buildings(vector<int> a){
	int n = sz(a);
	if(n > 130000){
		return vector<pi>();
	}
	seg.init(n);
	vector<int> dp(n);
	vector<vector<int>> dpval;
	for(int i = n - 1; i >= 0; i--){
		dp[i] = max(0, seg.query(a[i] - 1) + 1);
		seg.upd(a[i], dp[i]);
		if(sz(dpval) <= dp[i]){
			dpval.resize(dp[i] + 1);
		}
		dpval[dp[i]].push_back(i);
	}
	{
		vector<pi> vx, vy;
		for(int i = 0; i < n; i++){
			vx.emplace_back(i + 1, a[i]);
			vy.emplace_back(a[i], n + 1 - i);
		}
		segx.init(vx);
		segy.init(vy);
	}
	vector<int> ord(n);
	vector<int> rev = {-1};
	int cur_determined = 0;
	for(auto &v : dpval){
		sort(all(v), [&](int x, int y){
				if(x == y) return false;
				bool swp = 0;
				if(x > y) swap(x, y), swp = 1;
				int xonly = segx.query(x + 1, y, a[x] - 1);
				int yonly = segy.query(a[x], a[y] - 1, n - y);
				if(xonly < yonly) swp ^= 1;
				return swp;
				});
		for(auto &i : v) rev.push_back(i);
		for(int j = 0; j < sz(v); j++){
			ord[v[j]] = ++cur_determined;
			segx.add(v[j] + 1, a[v[j]], ord[v[j]]);
			segy.add(a[v[j]], n + 1 - v[j], ord[v[j]]);
		}
	}
	vector<int> proc(n);
	iota(all(proc), 0);
	sort(all(proc), [&](int x, int y){
			return ord[x] > ord[y];
			});
	vector<pi> ans;
	vector<int> killed(n);
	int cnt = 0;
	set<int> s;
	set<int> ord_s;
	{
		seg2.init(n);
		int curMax = 0;
		for(int j = 0; j < n; j++){
			seg2.upd(j, pi(a[j], j));
			if(curMax < a[j]){
				s.insert(j);
				ord_s.insert(ord[j]);
				curMax = a[j];
			}
		}
	}
	auto Erase = [&](int x){
		auto nxt = s.upper_bound(x);
		int y = (nxt == s.end() ? n : *nxt);
		s.erase(x);
		ord_s.erase(ord[x]);
		seg2.upd(x, pi(-1e9, x));
		while(y > 0){
			auto val = seg2.query(0, y - 1);
			if(s.find(val.second) != s.end()) break;
			if(val.first < 0) break;
			s.insert(val.second);
			ord_s.insert(ord[val.second]);
			y = val.second;
		}
	};
	while(cnt < n){
		if(sz(s) == 1){
			cnt++;
			int nd = rev[*ord_s.begin()];
			Erase(nd);
			ans.emplace_back(a[nd], n + 1);
		}
		else{
			cnt += 2;
			auto it = ord_s.end();
			int nd1 = rev[*--it];
			int nd2 = rev[*--it];
			Erase(nd1);
			Erase(nd2);
			ans.emplace_back(a[nd1], a[nd2]);
		}
	}
	return ans;
}

int main(){
	int n;
	assert(scanf("%d",&n) == 1);
	vector<int> a(n);
	for(int i = 0; i < n; i++) assert(scanf("%d",&a[i]) == 1);
	auto ans = min_shooting_buildings(a);
	printf("%d\n", (int)ans.size());
	for(auto &[x, y] : ans) printf("%d %d\n", x, y);
}