#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;
const int MAXN = 200050;
const int MAXT = 530000;

struct intv{
	int s, e; lint x;
};

struct query{
	int s, e; lint x; int idx;
};

struct bit{
	lint tree[MAXN];
	void add(int x, lint v){
		for(int i = x; i < MAXN; i += i & -i) tree[i] += v;
	}
	lint query(int x){
		lint ret = 0;
		for(int i = x; i; i -= i & -i) ret += tree[i];
		return ret;
	}
	lint query(int s, int e){ return query(e) - query(s - 1); }
	void clear(){
		memset(tree, 0, sizeof(tree));
	}
}bit1, bit2;

struct seg{
	int tree[MAXT], lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void upd(int x, int v){
		for(int i = x+lim; i; i >>= 1){
			tree[i] = max(tree[i], v);
		}
	}
	int query(int s, int e){
		s += lim;
		e += lim;
		int ret = 0;
		while(s < e){
			if(s%2 == 1) ret = max(ret, tree[s++]);
			if(e%2 == 0) ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = max(ret, tree[s]);
		return ret;
	}
}seg;

vector<lint> a, b;

void dnc1(vector<intv> &v, vector<query> &w, int s1, int e1, int s2, int e2, vector<lint> &ans){
	if(s1 > e1) return;
	if(s2 == e2){
		for(int x = s1; x <= e1; x++){
			if(v[x].s > w[s2].s && v[x].e <= w[s2].e){
				ans[w[s2].idx] += v[x].x * max(0ll, a[v[x].e] - a[v[x].s - 2] - w[s2].x);
			}
		}
		return;
	}
	int j = s1;
	int m = (s2 + e2) / 2;
	while(j <= e1 && a[v[j].e] - a[v[j].s - 2] < w[m].x) j++;
	dnc1(v, w, s1, j - 1, s2, m, ans);
	dnc1(v, w, j, e1, m + 1, e2, ans);
	vector<intv> nv(v.begin() + j, v.begin() + e1 + 1);
	vector<query> nw(w.begin() + s2, w.begin() + m + 1);
	sort(all(nv), [&](const intv &a, const intv &b){
		return a.e < b.e;
	});
	sort(all(nw), [&](const query &a, const query &b){
		return a.e < b.e;
	});
	int p = 0;
	for(auto &x : nw){
		while(p < sz(nv) && nv[p].e <= x.e){
			bit1.add(nv[p].s, nv[p].x * (a[nv[p].e] - a[nv[p].s - 2]));
			bit2.add(nv[p].s, nv[p].x);
			p++;
		}
		ans[x.idx] += bit1.query(x.s + 1, MAXN - 2) - x.x * bit2.query(x.s + 1, MAXN - 2);
	}
	while(p){
		p--;
		bit1.add(nv[p].s, -nv[p].x * (a[nv[p].e] - a[nv[p].s - 2]));
		bit2.add(nv[p].s, -nv[p].x);
	}
}

void dnc2(vector<intv> &v, vector<query> &w, int s1, int e1, int s2, int e2, vector<lint> &ans){
	if(s1 > e1) return;
	if(s2 == e2){
		for(int x = s1; x <= e1; x++){
			if(v[x].s > w[s2].s && v[x].e > w[s2].e){
				ans[w[s2].idx] += v[x].x * max(a[w[s2].e] - a[v[x].s - 2] - w[s2].x, 0ll);
			}
		}
		return;
	}
	int j = s1;
	int m = (s2 + e2) / 2;
	while(j <= e1 && a[v[j].s - 2] < a[w[m].e] - w[m].x) j++;
	dnc2(v, w, s1, j - 1, s2, m, ans);
	dnc2(v, w, j, e1, m + 1, e2, ans);
	vector<intv> nv(v.begin() + s1, v.begin() + j);
	vector<query> nw(w.begin() + m + 1, w.begin() + e2 + 1);
	sort(all(nv), [&](const intv &a, const intv &b){
		return a.e > b.e;
		});
	sort(all(nw), [&](const query &a, const query &b){
			return a.e > b.e;
			});
	int p = 0;
	for(auto &x : nw){
		while(p < sz(nv) && nv[p].e > x.e){
			bit1.add(nv[p].s, nv[p].x * (- a[nv[p].s - 2]));
			bit2.add(nv[p].s, nv[p].x);
			p++;
		}
		ans[x.idx] += bit1.query(x.s + 1, MAXN - 2) + (a[x.e] - x.x) * bit2.query(x.s + 1, MAXN - 2);
	}
	while(p){
		p--;
		bit1.add(nv[p].s, -nv[p].x * (- a[nv[p].s - 2]));
		bit2.add(nv[p].s, -nv[p].x);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	a.resize(n + 1);
	b.resize(n);
	seg.init(n);
	for(int i = 1; i <= n; i++){
		cin >> a[i], a[i] += a[i - 1];
		seg.upd(i, a[i] - a[i-1]);
	}
	for(int i = 0; i < n; i++) cin >> b[i];
	vector<intv> v;
	{
		vector<int> stk;
		vector<int> l(n), r(n);
		for(int i = 0; i < n; i++){
			while(sz(stk) && b[stk.back()] > b[i]){
				stk.pop_back();
			}
			l[i] = (sz(stk) ? stk.back() : -1);
			stk.push_back(i);
		}
		stk.clear();
		for(int i = n-1; i >= 0; i--){
			while(sz(stk) && b[stk.back()] >= b[i]){
				stk.pop_back();
			}
			r[i] = (sz(stk) ? stk.back() : n);
			stk.push_back(i);
		}
		stk.clear();
		for(int i = 0; i < n; i++){
			lint lo = 0;
			if(l[i] >= 0) lo = max(lo, b[l[i]]);
			if(r[i] < n) lo = max(lo, b[r[i]]);
			v.push_back({l[i] + 2, r[i], b[i] - lo});
		}
	}
	vector<lint> ans(m);
	vector<query> qry;
	for(int i = 0; i < m; i++){
		int s, e; lint x;
		cin >> s >> e >> x;
		e--;
		if(seg.query(s, e) > x){
			ans[i] = -1;
			continue;
		}
		qry.push_back({s, e, x, i});
	}
	sort(all(v), [&](const intv &a, const intv &b){
		return a.s < b.s;
	});
	sort(all(qry), [&](const query &a, const query &b){
		return a.s < b.s;
	});
	int pv = 0, pq = 0;
	for(int i = 1; i <= n; i++){
		while(pv < sz(v) && v[pv].s == i){
			bit1.add(v[pv].e, v[pv].x);
			bit2.add(v[pv].e, v[pv].x * a[v[pv].e]);
			pv++;
		}
		while(pq < sz(qry) && qry[pq].s == i){
			auto Q = qry[pq++];
			ans[Q.idx] += (a[Q.e] - a[Q.s - 1]) * bit1.query(Q.e, n);
			ans[Q.idx] += bit2.query(Q.s, Q.e - 1);
			ans[Q.idx] -= a[Q.s - 1] * bit1.query(Q.s, Q.e - 1);
		}
	}
	bit1.clear();
	bit2.clear();
	{
		vector<intv> nv;
		for(auto &i : v){
			if(i.s > 1) nv.push_back(i);
		}
		v = nv;
	}
	sort(all(v), [&](const intv &i, const intv &j){
		return a[i.e] - a[i.s - 2] < a[j.e] - a[j.s - 2];
	});
	sort(all(qry), [&](const query &a, const query &b){
		return a.x < b.x;
	});
	dnc1(v, qry, 0, sz(v) - 1, 0, sz(qry) - 1, ans);
	sort(all(v), [&](const intv &i, const intv &j){
		return i.s < j.s;
	});
	sort(all(qry), [&](const query &i, const query &j){
		return a[i.e] - i.x < a[j.e] - j.x;
	});
	dnc2(v, qry, 0, sz(v) - 1, 0, sz(qry) - 1, ans);
	for(auto &a : ans) cout << a << "\n";
}
