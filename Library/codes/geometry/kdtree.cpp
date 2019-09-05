typedef pair<int, int> pi;
struct node{
	pi pnt;
	int spl, sx, ex, sy, ey;
}tree[270000];

pi a[100005];
int n, ok[270000];

lint sqr(int x){ return 1ll * x * x; }
bool cmp1(pi a, pi b){ return a < b; }
bool cmp2(pi a, pi b){ return pi(a.second, a.first) < pi(b.second, b.first); }

// init(0, n-1, 1) : Initialize kd-tree
// set dap = INF, and call solve(1, P). dap = (closest point from P)
void init(int s, int e, int p){ // Initialize kd-tree
	int minx = 1e9, maxx = -1e9, miny = 1e9, maxy = -1e9;
	int m = (s+e)/2;
	for(int i=s; i<=e; i++){
		minx = min(minx, a[i].first);
		miny = min(miny, a[i].second);
		maxx = max(maxx, a[i].first);
		maxy = max(maxy, a[i].second);
	}
	tree[p].spl = (maxx - minx < maxy - miny);
	sort(a+s, a+e+1, [&](const pi &a, const pi &b){
		return tree[p].spl ? cmp2(a, b) : cmp1(a, b);
	});
	ok[p] = 1;
	tree[p] = {a[m], tree[p].spl, minx, maxx, miny, maxy};
	if(s <= m-1) init(s, m-1, 2*p);
	if(m+1 <= e) init(m+1, e, 2*p+1);
}

lint dap = 3e18;

void solve(int p, pi x){ // find closest point from point x (L^2)
	if(x != tree[p].pnt) dap = min(dap, sqr(x.first - tree[p].pnt.first) + sqr(x.second - tree[p].pnt.second));
	if(tree[p].spl){
		if(!cmp2(tree[p].pnt, x)){
			if(ok[2*p]) solve(2*p, x);
			if(ok[2*p+1] && sqr(tree[2*p+1].sy - x.second) < dap) solve(2*p+1, x);
		}
		else{
			if(ok[2*p+1]) solve(2*p+1, x);
			if(ok[2*p] && sqr(tree[2*p].ey - x.second) < dap) solve(2*p, x);
		}
	}
	else{
		if(!cmp1(tree[p].pnt, x)){
			if(ok[2*p]) solve(2*p, x);
			if(ok[2*p+1] && sqr(tree[2*p+1].sx - x.first) < dap) solve(2*p+1, x);
		}
		else{
			if(ok[2*p+1]) solve(2*p+1, x);
			if(ok[2*p] && sqr(tree[2*p].ex - x.first) < dap) solve(2*p, x);
		}
	}
}
