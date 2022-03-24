#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;
const int mod = 1e9 + 7;

struct disj{
	int pa[MAXN], rk[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
		memset(rk, 0, sizeof(rk));
	}
	int find(int x){
		return pa[x] == x ? x : find(pa[x]);
	}
	bool uni(int p, int q, vector<pi> &snapshot){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		if(rk[p] < rk[q]) swap(p, q);
		snapshot.push_back({q, pa[q]});
		pa[q] = p;
		if(rk[p] == rk[q]){
			snapshot.push_back({p, -1});
			rk[p]++;
		}
		return 1;
	}
	void revert(vector<pi> &snapshot){
		reverse(snapshot.begin(), snapshot.end());
		for(auto &x : snapshot){
			if(x.second < 0) rk[x.first]--;
			else pa[x.first] = x.second;
		}
		snapshot.clear();
	}
}disj;

struct edg{
	int s, e, x;
	bool operator<(const edg &e)const{
		return x > e.x;
	}
};

namespace Eppstein{
	int n, m, q;
	int st[MAXN], ed[MAXN], cost[MAXN], chk[MAXN];
	pi qr[MAXN];

	bool cmp(int &a, int &b){ return pi(cost[a], a) < pi(cost[b], b); }

	void contract(int s, int e, vector<int> v, vector<int> &must_mst, vector<int> &maybe_mst){
		sort(v.begin(), v.end(), cmp);
		vector<pi> snapshot;
		for(int i=s; i<=e; i++) disj.uni(st[qr[i].first], ed[qr[i].first], snapshot);
		for(auto &i : v) if(disj.uni(st[i], ed[i], snapshot)) must_mst.push_back(i);
		disj.revert(snapshot);
		for(auto &i : must_mst) disj.uni(st[i], ed[i], snapshot);
		for(auto &i : v) if(disj.uni(st[i], ed[i], snapshot)) maybe_mst.push_back(i);
		disj.revert(snapshot);
	}

	int max_found[MAXN];

	void solve(int s, int e, vector<int> v, lint cv){
		if(s == e){
			cost[qr[s].first] = qr[s].second;
			if(st[qr[s].first] == ed[qr[s].first]){
				return;
			}
			int minv = qr[s].first;
			for(auto &i : v){
				assert(st[i] != ed[i]);
				if(cmp(i, minv)){
					minv = i;
				}
			}
			max_found[minv] = max(max_found[minv], s + 1);
			return;
		}
		int m = (s+e)/2;
		vector<int> lv = v, rv = v;
		vector<int> must_mst, maybe_mst;
		for(int i=m+1; i<=e; i++){
			chk[qr[i].first]--;
			if(chk[qr[i].first] == 0) lv.push_back(qr[i].first);
		}
		vector<pi> snapshot;
		contract(s, m, lv, must_mst, maybe_mst);
		lint lcv = cv;
		for(auto &i : must_mst){
			lcv += cost[i], disj.uni(st[i], ed[i], snapshot);
			max_found[i] = max(max_found[i], m + 1);
		}
		solve(s, m, maybe_mst, lcv);
		disj.revert(snapshot);
		must_mst.clear(); maybe_mst.clear();
		for(int i=m+1; i<=e; i++) chk[qr[i].first]++;
		for(int i=s; i<=m; i++){
			chk[qr[i].first]--;
			if(chk[qr[i].first] == 0) rv.push_back(qr[i].first);
		}
		lint rcv = cv;
		contract(m+1, e, rv, must_mst, maybe_mst);
		for(auto &i : must_mst){
			rcv += cost[i], disj.uni(st[i], ed[i], snapshot);
			max_found[i] = max(max_found[i], e + 1);
		}
		solve(m+1, e, maybe_mst, rcv);
		disj.revert(snapshot);
		for(int i=s; i<=m; i++) chk[qr[i].first]++;
	}

	vector<lint> solve(int _n, int _m, vector<edg> e){
		memset(chk, 0, sizeof(chk));
		memset(max_found, 0, sizeof(max_found));
		n = _n;
		m = _m;
		q = _m;
		vector<int> ve;
		for(int i=0; i<m; i++){
			st[i] = e[i].s;
			ed[i] = e[i].e;
			cost[i] = 2.1e9;
		}
		for(int i=0; i<q; i++){
			qr[i].first = i;
			qr[i].second = e[i].x;
			chk[qr[i].first]++;
		}
		disj.init(n);
		for(int i=0; i<m; i++) if(!chk[i]) ve.push_back(i);
		solve(0, q-1, ve, 0);
		vector<lint> v(m);
		for(int i=0; i<m; i++){
			if(max_found[i] < m) v[i] = cost[max_found[i]];
			else v[i] = -1e10;
		}
		return v;
	}
}

struct event{
	lint pos, dx, val;
	bool operator<(const event &e)const{
		if(pos == e.pos) return dx > e.dx;
		return pos < e.pos;
	}
};

int main(){
	int n, m;
	scanf("%d %d",&n,&m);
	vector<edg> ed(m);
	for(int i=0; i<m; i++){
		scanf("%d %d %d",&ed[i].s,&ed[i].e,&ed[i].x);
	}
	sort(all(ed));
	vector<lint> up = Eppstein::solve(n, m, ed);
	reverse(all(ed));
	for(auto &i : ed) i.x = -i.x;
	vector<lint> dn = Eppstein::solve(n, m, ed);
	for(auto &i : ed) i.x = -i.x;
	reverse(all(ed));
	reverse(all(dn));
	vector<event> v;
	for(int i=0; i<m; i++){
		dn[i] *= -1;
		up[i] = min(up[i], 1ll * ed[i].x);
		dn[i] = max(dn[i], 1ll * ed[i].x);
		lint l = (ed[i].x + up[i]);
		lint r = (ed[i].x + dn[i]);
		if(l < r){
			v.push_back({l, +1, ed[i].x});
			v.push_back({r, -1, ed[i].x});
		}
	}
	sort(all(v));
	int q; scanf("%d",&q);
	multiset<int> s;
	int ptr = 0;
	for(int i = 0; i < q; i++){
		int x; scanf("%d",&x);
		while(ptr < sz(v) && v[ptr].pos <= x * 2){
			if(v[ptr].dx == +1) s.insert(v[ptr].val);
			else s.erase(s.find(v[ptr].val));
			ptr++;
		}
		lint ret = 0;
		for(auto &y : s){
			ret += abs(x - y);
		}
		printf("%lld\n", ret);
	}
}
