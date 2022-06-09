#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 100005;
const int MAXT = 270000;

lint a[MAXN];

struct node{
	int s, e, cost;
	bool operator<(const node &nd)const{
		return pi(s, -e) < pi(nd.s, -nd.e);
	}
	bool operator==(const node &nd)const{
		return pi(s, -e) == pi(nd.s, -nd.e);
	}
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
	lint query(int s, int e){
		if(s > e) return 0;
		return query(e) - query(s - 1);
	}
}bit, subs;

struct seg{
	lint tree[MAXT];
	void init(int s, int e, int p, lint *a){
		if(s == e){
			tree[p] = a[s];
			return;
		}
		int m = (s+e)/2;
		init(s, m, 2*p, a);
		init(m+1, e, 2*p+1, a);
		tree[p] = max(tree[2*p], tree[2*p+1]);
	}
	void upd(int pos, int s, int e, int p, lint v){
		if(s == e){
			tree[p] = v;
			return;
		}
		int m = (s + e) / 2;
		if(pos <= m) upd(pos, s, m, 2*p, v);
		else upd(pos, m+1, e, 2*p+1, v);
		tree[p] = max(tree[2*p], tree[2*p+1]);
	}
	int queryLeft(int s, int e, int ps, int pe, int p, lint v){
		if(e < ps || pe < s) return 1e9;
		if(tree[p] <= v) return 1e9;
		if(ps == pe) return ps;
		int pm = (ps + pe) / 2;
		if(s <= ps && pe <= e){
			if(tree[2*p] > v) return queryLeft(s, e, ps, pm, 2*p, v);
			return queryLeft(s, e, pm+1, pe, 2*p+1, v);
		}
		int r = queryLeft(s, e, ps, pm, 2*p, v);
		if(r < 1e7) return r;
		return queryLeft(s, e, pm+1, pe, 2*p+1, v);
	}
	int queryRight(int s, int e, int ps, int pe, int p, lint v){
		if(e < ps || pe < s) return -1e9;
		if(tree[p] <= v) return -1e9;
		if(ps == pe) return ps;
		int pm = (ps + pe) / 2;
		if(s <= ps && pe <= e){
			if(tree[2*p+1] > v) return queryRight(s, e, pm+1, pe, 2*p+1, v);
			return queryRight(s, e, ps, pm, 2*p, v);
		}
		int r = queryRight(s, e, pm+1, pe, 2*p+1, v);
		if(r > 0) return r;
		return queryRight(s, e, ps, pm, 2*p, v);
	}
}seg;

int n;
set<node> st;

void getNodeSet(int x, vector<node> &v){
	if(x < 2 || x >= n) return;
	int l = x, r = x;
	while(true){
		lint curSum = bit.query(l, r);
		if(curSum < min(a[l-1], a[r+1])){
			v.push_back({l, r, -1});
			if(l == 2 && r == n - 1) break;
			if(a[l-1] < a[r+1]) l--;
			else r++;
		}
		curSum = bit.query(l, r);
		int leftClosest = seg.queryRight(1, l - 1, 1, n, 1, curSum);
		int rightClosest = seg.queryLeft(r + 1, n, 1, n, 1,	curSum);
		l = leftClosest + 1;
		r = rightClosest - 1;
	}
}

void add(int x, int v){
	vector<node> l;
	getNodeSet(x-1, l);
	getNodeSet(x, l);
	getNodeSet(x+1, l);
	sort(all(l));
	reverse(all(l));
	l.resize(unique(all(l)) - l.begin());
	for(auto &x : l){
		auto it = st.lower_bound({x.s, x.e, -1});
		if(it != st.end() && it->s == x.s && it->e == x.e){
			//			cout << "erase interval " << x.s << " " << x.e << " " << it->cost << endl;
			subs.add(it->s - 1, -it->cost);
			st.erase(it);
		}
		else assert(0);
	}
	l.clear();
	bit.add(x, v);
	a[x] += v;
	seg.upd(x, 1, n, 1, a[x]);
	getNodeSet(x-1, l);
	getNodeSet(x, l);
	getNodeSet(x+1, l);
	sort(all(l));
	reverse(all(l));
	l.resize(unique(all(l)) - l.begin());
	for(auto &x : l){
		auto it = st.lower_bound({x.s, x.e, -1});
		if(it != st.end() && it->s == x.s && it->e == x.e){
			assert(0);
		}
		int sum = subs.query(x.s - 1, x.e);
		subs.add(x.s - 1, x.e - x.s + 1 - sum);
		st.insert({x.s, x.e, x.e - x.s + 1 - sum});
		//		cout << "Add interval " << x.s << " " << x.e << " " << x.e - x.s + 1 - sum << endl;
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	a[1] = a[n + 2] = 1e15;
	for(int i = 2; i <= n + 1; i++){
		cin >> a[i];
	}
	n += 2;
	seg.init(1, n, 1, a);
	for(int i = 1; i <= n; i++){
		bit.add(i, a[i]);
	}
	vector<node> l;
	for(int i = 2; i <= n - 1; i++){
		getNodeSet(i, l);
	}
	sort(all(l));
	reverse(all(l));
	l.resize(unique(all(l)) - l.begin());
	for(auto &x : l){
		auto it = st.lower_bound({x.s, x.e, -1});
		if(it != st.end() && it->s == x.s && it->e == x.e){
			assert(0);
		}
		int sum = subs.query(x.s - 1, x.e);
		subs.add(x.s - 1, x.e - x.s + 1 - sum);
		st.insert({x.s, x.e, x.e - x.s + 1 - sum});
		//		cout << "Add interval " << x.s << " " << x.e << " " << x.e - x.s + 1 - sum << endl;
	}
	int q; cin >> q;
	while(q--){
		int t, x, y; cin >> t >> x >> y;
		if(t == 1){
			x++;
			add(x, y - a[x]);
		}
		else{
			x++; y++;
			int sx = x, sy = y;
			for(int i = x; i < y; ){
				int j = seg.queryLeft(i + 1, y, 1, n, 1, bit.query(x, i));
				if(j > 1e8) break;
				if(bit.query(x, j - 1) < a[j]) sx = j;
				i = j;
			}
			for(int i = y; i > x; ){
				int j = seg.queryRight(x, i - 1, 1, n, 1, bit.query(i, y));
				if(j < 0) break;
				if(bit.query(j + 1, y) < a[j]) sy = j;
				i = j;
			}
			cout << sy - sx + 1 - subs.query(sx, sy - 1) << "\n";
		}
	}
}
