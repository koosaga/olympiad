#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;
const int MAXT = 530000;
const int MAXC = 250000;

struct seg{
	int tree[MAXT];
	int lazy[MAXT];
	void clear(){
		memset(tree, 0, sizeof(tree));
		memset(lazy, 0, sizeof(lazy));
	}
	void lazydown(int p){
		for(int i=2*p; i<2*p+2; i++){
			tree[i] += lazy[p];
			lazy[i] += lazy[p];
		}
		lazy[p] = 0;
	}
	void upd(int s, int e, int ps, int pe, int p, int v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p] += v;
			lazy[p] += v;
			return;
		}
		if(lazy[p]) lazydown(p);
		int pm = (ps+pe)/2;
		upd(s, e, ps, pm, 2*p, v);
		upd(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = max(tree[2*p], tree[2*p+1]);
	}
	void add(int s, int e, int x){
		e = min(e, MAXC);
		if(s <= e){
			upd(s, e, 1, MAXC, 1, x); 
		}
	}
}seg;

struct point{
	int x, y, c;
}a[MAXN];

int n, k;

bool trial(int X){
	multiset<int> s[MAXN];
	auto add_point = [&](point p){
		auto it = s[p.c].lower_bound(p.y);
		int LEFT = (it != s[p.c].begin() ? *prev(it) : -1e9);
		int RIGHT = (it != s[p.c].end() ? *it : 1e9);
		// cut down previous one's range
		int st = p.y;
		if(LEFT >= 0){
			int appRange = min(X + 1, RIGHT - LEFT);
			st = max(st, LEFT + appRange);
		}
		// add my range
		int appRange = min(X + 1, RIGHT - p.y);
		seg.add(st, p.y + appRange - 1, +1);
		s[p.c].insert(p.y);
	};
	auto remove_point = [&](point p){
		auto it = s[p.c].erase(s[p.c].find(p.y));
		int LEFT = (it != s[p.c].begin() ? *prev(it) : -1e9);
		int RIGHT = (it != s[p.c].end() ? *it : 1e9);
		int appRange = min(X + 1, RIGHT - p.y);
		// remove my range
		int st = p.y;
		if(LEFT >= 0){
			// calculate previously excluded range, if it exists
			int appRange = min(X + 1, RIGHT - LEFT);
			st = max(st, LEFT + appRange);
		}
		seg.add(st, p.y + appRange - 1, -1);
	};
	int j = 0;
	seg.clear();
	for(int i=0; i<n; i++){
		add_point(a[i]);
		while(a[j].x < a[i].x - X) remove_point(a[j++]);
		if(seg.tree[1] == k) return 1;
	}
	return 0;
}

int main(){
	scanf("%d %d",&n,&k);
	for(int i=0; i<n; i++){
		scanf("%d %d %d",&a[i].x,&a[i].y,&a[i].c);
	}
	sort(a, a + n, [&](const point &x, const point &y){
		return x.x < y.x;
	});
	int s = 0, e = 250000;
	while(s != e){
		int m = (s + e) / 2;
		if(trial(m)) e = m;
		else s = m + 1;
	}
	cout << s << endl;
}
