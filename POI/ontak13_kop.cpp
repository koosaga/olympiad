#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXT = (1 << 21) + 10;
const int MAXN = 1000000;

int n, q;

struct swp1{
	int pos, s, e, dx;
	bool operator<(const swp1 &s)const{
		return pos < s.pos;
	}
};

struct swp2{
	int pos, s, e, dx, idx;
	bool operator<(const swp2 &s)const{
		return pos < s.pos;
	}
};

struct seg{
	lint tree[MAXT], lazy[MAXT];
	void lazydown(int p, int s, int e){
		int m = (s+e)/2;
		tree[2*p] += lazy[p] * (m - s + 1);
		tree[2*p+1] += lazy[p] * (e - m);
		lazy[2*p] += lazy[p];
		lazy[2*p+1] += lazy[p];
		lazy[p] = 0;
	}
	void add(int s, int e, int ps, int pe, int p, int v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p] += 1ll * (pe - ps + 1) * v;
			lazy[p] += v;
			return;
		}
		int pm = (ps + pe) / 2;
		lazydown(p, ps, pe);
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = tree[2*p] + tree[2*p+1];
	}
	lint query(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return 0;
		if(s <= ps && pe <= e) return tree[p];
		int pm = (ps + pe) / 2;
		lazydown(p, ps, pe);
		return query(s, e, ps, pm, 2*p) + query(s, e, pm+1, pe, 2*p+1);
	}
}cseg, xseg;

vector<swp1> v1;
vector<swp2> v2;

lint ans[MAXN];

void solve(){
	int ptr1 = 0;
	int ptr2 = 0;
	for(int i=0; i<=MAXN; i++){
		while(ptr1 < v1.size() && v1[ptr1].pos == i){
			xseg.add(v1[ptr1].s, v1[ptr1].e, 0, MAXN, 1, v1[ptr1].dx);
			cseg.add(v1[ptr1].s, v1[ptr1].e, 0, MAXN, 1, -v1[ptr1].dx * v1[ptr1].pos);
			ptr1++;
		}
		while(ptr2 < v2.size() && v2[ptr2].pos == i){
			ans[v2[ptr2].idx] += v2[ptr2].dx * 
			(cseg.query(v2[ptr2].s, v2[ptr2].e, 0, MAXN, 1) +
			i * xseg.query(v2[ptr2].s, v2[ptr2].e, 0, MAXN, 1));
			ptr2++;
		}
	}
}

int main(){
	int l, w;
	scanf("%d %d %d %d",&n,&q,&l,&w);
	for(int i=0; i<n; i++){
		int sx, ex, sy, ey;
		scanf("%d %d %d %d",&sx,&sy,&ex,&ey);
		v1.push_back({sx, sy, ey-1, 1});
		v1.push_back({ex, sy, ey-1, -1});
	}
	for(int i=0; i<q; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		v2.push_back({x, y, y+w-1, -1, i});
		v2.push_back({x+l, y, y+w-1, 1, i});
	}
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	solve();
	for(int i=0; i<q; i++) printf("%lld\n", ans[i]);
}
