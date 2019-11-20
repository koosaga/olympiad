#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 200005;
const int B = 256;

struct query{
	int s, e, x;
	bool operator<(const query &q)const{
		int v = (s / B);
		int w = (q.s / B);
		if(v != w) return v < w;
		if(v & 1) return e > q.e;
		return e < q.e;
	}
};

struct node{
	int l, r, s, v;
};

node merge(node &ret, node &l, node &r){
	ret.l = l.l + (l.s == l.l ? r.l : 0);
	ret.r = r.r + (r.s == r.r ? l.r : 0);
	ret.v = max({l.v, r.v, l.r + r.l});
	return ret;
}

struct segtree{
	node tree[132000];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		for(int i=0; i<n; i++){
			tree[i + lim] = {0, 0, 1, 0};
		}
		for(int i=lim-1; i>=0; i--){
			tree[i].s = tree[2*i].s + tree[2*i+1].s;
			merge(tree[i], tree[2*i], tree[2*i+1]);
		}
	}
	void upd(int x, int v){
		x += lim;
		tree[x] = {v, v, tree[x].s, v};
		while(x > 1){
			x >>= 1;
			merge(tree[x],tree[2*x], tree[2*x+1]);
		}
	}
	node query(){
		return tree[1];
	}
}seg;

int n, q;
int s[MAXN], e[MAXN];
int mode[MAXN], pos[MAXN], ret[MAXN];
vector<query> qry;

void Do(){
	seg.init(n);
	for(int i=0; i<n; i++){
		if(e[i] < qry[0].s || qry[0].e < s[i]) continue;
		seg.upd(i, 1);
	}
	ret[qry[0].x] = seg.query().v;
	int ps = qry[0].s, pe = qry[0].e;
	for(int i=1; i<qry.size(); i++){
		while(ps > qry[i].s){
			ps--;
			if(mode[ps] == 1) seg.upd(pos[ps], 1);
		}
		while(pe < qry[i].e){
			pe++;
			if(mode[pe] == 0) seg.upd(pos[pe], 1);
		}
		while(ps < qry[i].s){
			if(mode[ps] == 1) seg.upd(pos[ps], 0);
			ps++;
		}
		while(pe > qry[i].e){
			if(mode[pe] == 0) seg.upd(pos[pe], 0);
			pe--;
		}
		ret[qry[i].x] = seg.query().v;
	}
}

int main(){
	scanf("%d %d",&n,&q);
	vector<pi> v;
	for(int i=0; i<n; i++){
		scanf("%d %d",&s[i],&e[i]);
		s[i] = s[i] * 2;
		e[i] = e[i] * 2 + 1;
		v.push_back(pi(s[i], i));
		v.push_back(pi(e[i], i));
	}
	sort(v.begin(), v.end());
	for(int i=0; i<n; i++){
		s[i] = lower_bound(v.begin(), v.end(), pi(s[i], i)) - v.begin();
		e[i] = lower_bound(v.begin(), v.end(), pi(e[i], i)) - v.begin();
		mode[s[i]] = 0;
		mode[e[i]] = 1;
		pos[s[i]] = i;
		pos[e[i]] = i;
	}
	for(int i=0; i<q; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		s = 2 * s, e = 2 * e + 1;
		s = lower_bound(v.begin(), v.end(), pi(s, -1)) - v.begin();
		e = lower_bound(v.begin(), v.end(), pi(e, 1e9)) - v.begin() - 1;
		qry.push_back({s, e, i});
	}
	sort(qry.begin(), qry.end());
	Do();
	for(int i=0; i<q; i++) printf("%d\n", ret[i]);
}
