#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

struct point{
	int l, r, idx;
};

struct query{
	int t, i, j, k;
};

const int MAXN = 1500005;
const int MAXT = 4200000;
int went[MAXN];
pi ans[MAXN];
point stk[MAXN];

struct segL{
	pi tree[MAXT];
	int lim;
	void init(int n){
		fill(tree, tree + MAXT, pi(2e9, -1));
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void upd(int x, pi v){
		x += lim;
		tree[x] = v;
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(2e9, -1);
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}segL;

struct segR{
	pi tree[MAXT];
	int lim;
	void init(int n){
		fill(tree, tree + MAXT, pi(-2e9, -1));
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
		pi ret(-2e9, -1);
		while(s < e){
			if(s%2 == 1) ret = max(ret, tree[s++]);
			if(e%2 == 0) ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = max(ret, tree[s]);
		return ret;
	}
}segR;

void solve(int s, int e, vector<query> &queries){
	{
		bool ok = 0;
		for(auto &z : queries){
			if(z.t == 4) ok = 1;
		}
		if(!ok) return;
	}
	int m = (s + e) / 2;
	vector<query> L, R;
	int cnt = 0;
	vector<pi> stkL, stkR;
	auto getActual = [&](int pos){
		pi ret(stk[pos].l, stk[pos].r);
		{
			int s = 0, e = sz(stkL);
			while(s != e){
				int m = (s + e) / 2;
				if(stkL[m].second <= pos) s = m + 1;
				else e = m;
			}
			if(s < sz(stkL)) ret.first = max(ret.first, stkL[s].first);
		}
		{
			int s = 0, e = sz(stkR);
			while(s != e){
				int m = (s + e) / 2;
				if(stkR[m].second <= pos) s = m + 1;
				else e = m;
			}
			if(s < sz(stkR)) ret.second = min(ret.second, stkR[s].first);
		}
		return ret;
	};
	for(auto &x : queries){
		if(x.t == 1){
			if(went[x.i] == 1) L.push_back(x);
			else if(went[x.i] == 2) R.push_back(x);
			else{
				ans[x.j] = getActual(-went[x.i]);
			}
		}
		if(x.t == 2){
			if(x.i > m){
				int s = 0, e = sz(stkR);
				while(s != e){
					int m = (s + e) / 2;
					if(stkR[m].first <= x.i) s = m + 1;
					else e = m;
				}
				int l = (s ? stkR[s - 1].second : 0);
				while(true){
					auto q = segR.query(l, cnt - 1);
					if(q.first > x.i){
						int i = q.second;
						went[stk[i].idx] = 2;
						R.push_back({4, x.i, getActual(i).second, stk[i].idx});
						segL.upd(i, pi(2e9, -1));
						segR.upd(i, pi(-2e9, -1));
					}
					else break;
				}
				R.push_back(x);
			}
			else{
				while(sz(stkL) && stkL.back().first <= x.i){
					stkL.pop_back();
				}
				stkL.emplace_back(x.i, cnt);
				L.push_back(x);
			}
		}
		if(x.t == 3){
			if(x.i <= m){
				int s = 0, e = sz(stkL);
				while(s != e){
					int m = (s + e) / 2;
					if(stkL[m].first >= x.i) s = m + 1;
					else e = m;
				}
				int l = (s ? stkL[s - 1].second : 0);
				while(true){
					auto q = segL.query(l, cnt - 1);
					if(q.first < x.i){
						int i = q.second;
						went[stk[i].idx] = 1;
						L.push_back({4, getActual(i).first, x.i, stk[i].idx});
						segL.upd(i, pi(2e9, -1));
						segR.upd(i, pi(-2e9, -1));
					}
					else break;
				}
				L.push_back(x);
			}
			else{
				while(sz(stkR) && stkR.back().first >= x.i){
					stkR.pop_back();
				}
				stkR.emplace_back(x.i, cnt);
				R.push_back(x);
			}
		}
		if(x.t == 4){
			if(x.j <= m){
				went[x.k] = 1;
				L.push_back(x);
			}
			else if(x.i > m){
				went[x.k] = 2;
				R.push_back(x);
			}
			else{
				went[x.k] = -cnt;
				stk[cnt++] = (point){x.i, x.j, x.k};
				segL.upd(cnt - 1, pi(x.i, cnt - 1));
				segR.upd(cnt - 1, pi(x.j, cnt - 1));
			}
		}
	}
	for(auto &x : L){
		if(x.t == 4) went[x.k] = 0;
	}
	for(auto &x : R){
		if(x.t == 4) went[x.k] = 0;
	}
	for(int i = 0; i < cnt; i++){
		went[stk[i].idx] = 0;
		segL.upd(i, pi(2e9, -1));
		segR.upd(i, pi(-2e9, -1));
	}
	solve(s, m, L);
	solve(m + 1, e, R);
}

int main(){	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, q;
	cin >> n >> m >> q;
	vector<query> queries;
	segL.init(m + q);
	segR.init(m + q);
	for(int i = 0; i < m; i++){
		int x, y; cin >> x >> y;
		queries.push_back({4, x, n - y + 1, i});
	}
	int p = 0;
	for(int i = 0; i < q; i++){
		query Q; cin >> Q.t >> Q.i;
		if(Q.t == 4) cin >> Q.j;
		if(Q.t == 1) Q.i--, Q.j = p++;
		if(Q.t == 2) Q.i = n - Q.i;
		if(Q.t == 3) Q.i++;
		if(Q.t == 4) Q.j = n - Q.j + 1, Q.k = m++;
		queries.push_back(Q);
	}
	solve(0, n + 1, queries);
	for(int i = 0; i < p; i++) cout << ans[i].first << " " << n + 1 - ans[i].second << "\n";
}
