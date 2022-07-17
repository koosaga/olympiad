#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 200005;
const int mod = 998244353; //1e9 + 7;//998244353;

struct fuck{
	int sum, psum, ssum, opt;
	fuck(): sum(0), psum(0), ssum(0), opt(0) {}
	fuck operator+(const fuck &f)const{
		fuck ret;
		ret.sum = sum + f.sum;
		ret.psum = max(psum, sum + f.psum);
		ret.ssum = max(f.ssum, f.sum + ssum);
		ret.opt = max({opt, f.opt, ssum + f.psum});
		return ret;
	}
};

struct node{
	int l, r;
	fuck info;
};

node tree[6969696];
int piv;

int newnode(){ return ++piv; }

void init(int s, int e, int p){
	if(s == e) return;
	int m = (s + e) / 2;
	tree[p].l = newnode();
	tree[p].r = newnode();
	init(s, m, tree[p].l);
	init(m+1, e, tree[p].r);
}

void add(int s, int e, int p, int v, int l, int r){
	if(s == e){
		tree[r].info = tree[l].info;
		tree[r].info.sum += v;
		tree[r].info.psum = tree[r].info.ssum = tree[r].info.opt = max(tree[r].info.sum, 0);
		return;
	}
	int m = (s + e) / 2;
	if(p <= m){
		tree[r].l = newnode();
		tree[r].r = tree[l].r;
		add(s, m, p, v, tree[l].l, tree[r].l);
	}
	else{
		tree[r].r = newnode();
		tree[r].l = tree[l].l;
		add(m+1, e, p, v, tree[l].r, tree[r].r);
	}
	tree[r].info = tree[tree[r].l].info + tree[tree[r].r].info;
}

fuck query(int s, int e, int ps, int pe, int p){
	if(e < ps || pe < s) return fuck();
	if(s <= ps && pe <= e) return tree[p].info;
	int pm = (ps + pe) / 2;
	return query(s, e, ps, pm, tree[p].l) + query(s, e, pm+1, pe, tree[p].r);
}

struct point{
	int x, y, v;
	bool operator<(const point &p)const{
		return pi(x, y) < pi(p.x, p.y);
	}
};

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int w, h, n;
	cin >> w >> h >> n;
	vector<point> a(n);
	for(int i = 0; i < n; i++){
		cin >> a[i].x >> a[i].y >> a[i].v;
	}
	sort(all(a));
	vector<int> pst(n + 1);
	pst[0] = newnode();
	init(1, h, pst[0]);
	for(int i = 0; i < n; i++){
		pst[i + 1] = newnode();
		add(1, h, a[i].y, a[i].v, pst[i], pst[i + 1]);
	}
	int q; cin >> q;
	vector<int> ans(q + 1);
	for(int i = 1; i <= q; i++){
		int d, x, y; cin >> d >> x >> y;
		d ^= ans[max(i - 3, 0)];
		x ^= ans[max(i - 2, 0)];
		y ^= ans[max(i - 1, 0)];
		int pos = lower_bound(all(a), (point){d + 1, -1, -1}) - a.begin();
		ans[i] = query(x, y, 1, h, pst[pos]).opt;
		cout << ans[i] << "\n";
	}
}
