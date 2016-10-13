#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

struct line_sweep{
	int pos;
	int st, ed;
	int add;
};

bool cmp(line_sweep a, line_sweep b){
	return a.pos < b.pos;
}

int sx, sy, ex, ey, l, n;
vector<line_sweep> v;

struct segtree{
	int tree[2100000], lazy[2100000];
	void lazydown(int p){
		lazy[2*p] += lazy[p];
		lazy[2*p+1] += lazy[p];
		tree[2*p] += lazy[p];
		tree[2*p+1] += lazy[p];
		lazy[p] = 0;
	}
	void add(int s, int e, int ps, int pe, int p, int v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			lazy[p] += v;
			tree[p] += v;
			return;
		}
		lazydown(p);
		int pm = (ps+pe)/2;
		add(s,e,ps,pm,2*p,v);
		add(s,e,pm+1,pe,2*p+1,v);
		tree[p] = max(tree[2*p],tree[2*p+1]);
	}
}seg;

int main(){
	int w, h;
	scanf("%d %d %d",&w,&h,&n);
	for (int i=0; i<n; i++) {
		int x1, y1;
		scanf("%d %d",&x1,&y1);
		x1 += 50000;
		y1 += 50000;
		v.push_back({y1-h, x1-w, x1, 1});
		v.push_back({y1+1, x1-w, x1, -1});
	}
	sort(v.begin(),v.end(),cmp);
	int ret = 0;
	for (int i=0; i<v.size(); ) {
		int e = i;
		while (v[e].pos == v[i].pos) {
			e++;
		}
		for (int j=i; j<e; j++) {
			seg.add(v[j].st,v[j].ed,0,200000,1,v[j].add);
		}
		ret = max(ret,seg.tree[1]);
		i = e;
	}
	printf("%d",ret);
}
