#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
 
struct segtree{
	pi tree[530000];
	int lazy[530000];
	void init(int s, int e, int p){
		if(s == e) tree[p] = pi(1, s);
		else{
			int m = (s+e)/2;
			init(s, m, 2*p);
			init(m+1, e, 2*p+1);
			tree[p] = max(tree[2*p], tree[2*p+1]);
		}
	}
	void lazydown(int p){
		lazy[2*p] += lazy[p];
		lazy[2*p+1] += lazy[p];
		tree[2*p].first += lazy[p];
		tree[2*p+1].first += lazy[p];
		lazy[p] = 0;
	}
	pi query(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return pi(-1e9, -1e9);
		if(s <= ps && pe <= e) return tree[p];
		int pm = (ps+pe)/2;
		if(lazy[p]) lazydown(p);
		return max(query(s, e, ps, pm, 2*p), query(s, e, pm+1, pe, 2*p+1));
	}
	void update(int s, int e, int ps, int pe, int p, int v){
		if(s <= ps && pe <= e){
			lazy[p] += v;
			tree[p].first += v;
			return;
		}
		if(lazy[p]) lazydown(p);
		int pm = (ps+pe)/2;
		if(pm >= s) update(s, e, ps, pm, 2*p, v);
		if(e >= pm + 1) update(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = max(tree[2*p], tree[2*p+1]);
	}
};
 
struct segmax{
	segtree s;
	int n;
	void init(int _n){
		n = _n;
		s.init(1, n, 1);
	}
	void increase(int l, int r){
		s.update(l, r, 1, n, 1, 1);
	}
	vector<int> remove(int l, int r, int k){
		vector<int> v;
		while(true){
			auto x = s.query(l, r, 1, n, 1);
			if(x.first > k){
				v.push_back(x.second);
				s.update(x.second, x.second, 1, n, 1, -1e7);
			}
			else break;
		}
		return v;
	}
	void feed(vector<int> &v){
		for(auto &i : v) s.update(i, i, 1, n, 1, -1e7);
	}
	int count(int n, int k){
		int ans = 0;
		for(int i=1; i<=n; i++) if(s.query(i, i, 1, n, 1).first == k) ans++;
		return ans;
	}
}segmax;
 
struct segmin{
	segtree s;
	int n;
	void init(int _n){
		n = _n;
		s.init(1, n, 1);
		s.update(1, n, 1, n, 1, -2);
	}
	void increase(int l, int r){
		s.update(l, r, 1, n, 1, -1);
	}
	vector<int> remove(int l, int r, int k){
		vector<int> v;
		while(true){
			auto x = s.query(l, r, 1, n, 1);
			if(-x.first < k){
				v.push_back(x.second);
				s.update(x.second, x.second, 1, n, 1, -1e7);
			}
			else break;
		}
		return v;
	}
	void feed(vector<int> &v){
		for(auto &i : v) s.update(i, i, 1, n, 1, -1e7);
	}
}segmin;
 
int n, k;

struct bit{
	int tree[200005];
	void add(int x, int v){
		while(x <= n){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}return ret;
	}
}bit;
int FUCK[200005];

int main(){
	scanf("%d %d",&n,&k);
	segmax.init(n);
	segmin.init(n);
	int q; scanf("%d", &q);
	for(int i=1; i<=q; i++){
		int s, e, k;
		scanf("%d %d %d",&s,&e,&k);	
		if(bit.query(e) - e == bit.query(s-1) - (s-1)) continue;
		auto l = segmax.remove(s, e, k);
		segmin.feed(l);
		for(auto &i : l){
				bit.add(i, 1);
		}
		auto r = segmin.remove(s, e, k);
		for(auto &i : r){
				bit.add(i, 1);
		}
		segmax.feed(r);
		segmax.increase(s, e);
		segmin.increase(s, e);
	}
	cout << segmax.count(n, k + 1) << endl;
}

