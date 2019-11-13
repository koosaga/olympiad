#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
const int MAXT = 4100;
using lint = long long;

struct point{
	int x, y, w;
}a[MAXN];

int n;
struct node{
	lint l, r, opt, sum;
};

node operator+(node l, node r){
	node ans;
	ans.l = max(l.l, l.sum + r.l);
	ans.r = max(r.r, r.sum + l.r);
	ans.sum = l.sum + r.sum;
	ans.opt = max({l.opt, r.opt, l.r + r.l}); 
	return ans;
}

struct seg{
	node tree[MAXT];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n + 2; lim <<= 1);
		fill(tree, tree + MAXT, (node){0, 0, 0, 0});
	}
	void upd(int x, int v){
		x += lim;
		tree[x].sum += v;
		tree[x].l += v;
		tree[x].r += v;
		tree[x].opt += v;
		while(x > 1){
			x >>= 1;
			tree[x] = tree[2*x] + tree[2*x+1];
		}
	}
}seg;

int main(){
	int n1, n2;
	vector<int> crd;
	scanf("%d",&n1);
	for(int i=0; i<n1; i++){
		scanf("%d %d",&a[i].x,&a[i].y);
		a[i].w = +1;
		crd.push_back(a[i].y);
	}
	scanf("%d",&n2);
	for(int i=n1; i<n1+n2; i++){
		scanf("%d %d",&a[i].x,&a[i].y);
		a[i].w = -1;
		crd.push_back(a[i].y);
	}
	int c1, c2; scanf("%d %d",&c1,&c2);
	n = n1 + n2;
	for(int i=0; i<n; i++){
		if(a[i].w == +1) a[i].w = c1;
		else a[i].w = -c2;
	}
	sort(crd.begin(), crd.end());
	crd.resize(unique(crd.begin(), crd.end()) - crd.begin());
	for(int i=0; i<n; i++){
		a[i].y = lower_bound(crd.begin(), crd.end(), a[i].y) - crd.begin();
	}
	sort(a, a + n, [&](const point &x, const point &y){
			return x.x < y.x;
			});
	lint ret = 0;
	for(int i=0; i<n; i++){
		if(i && a[i-1].x == a[i].x) continue;
		seg.init(n);
		for(int j=i; j<n; j++){
			seg.upd(a[j].y, a[j].w);
			if(j+1<n && a[j+1].x == a[j].x) continue;
			ret = max(ret, seg.tree[1].opt);
		}
	}
	cout << ret << endl;
}


