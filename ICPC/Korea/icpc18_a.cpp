#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 100005;
const int MAXT = 530000;
using pi = pair<int, int>;
#define sz(v) int((v).size())

struct seg{
	int tree[MAXT], lazy[MAXT];
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
			tree[p] += v;
			lazy[p] += v;
			return;
		}
		int pm = (ps+pe)/2;
		lazydown(p);
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = max(tree[2*p], tree[2*p+1]);
	}
}seg;

struct swp{
	int s, e, x;
};

int n; 
pi a[MAXN];
vector<int> v;
vector<swp> ev[2 * MAXN];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%*d %d %*d %d",&a[i].second, &a[i].first);
		v.push_back(a[i].first);
		v.push_back(a[i].second);
	}
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	for(int i=0; i<n; i++){
		a[i].first = lower_bound(v.begin(), v.end(), a[i].first) - v.begin();
		a[i].second = lower_bound(v.begin(), v.end(), a[i].second) - v.begin();
		ev[0].push_back({a[i].first, a[i].second, +1});
		ev[a[i].first].push_back({a[i].first, a[i].second, -1});
		ev[a[i].first].push_back({0, sz(v) - 1, +1});
		ev[a[i].second+1].push_back({0, sz(v) - 1, -1});
		ev[a[i].second+1].push_back({a[i].first, a[i].second, +1});
	}
	int ret = 0;
	for(int i=0; i<sz(v); i++){
		for(auto &j : ev[i]) seg.add(j.s, j.e, 0, sz(v) - 1, 1, j.x);
		ret = max(ret, seg.tree[1]);
	}
	cout << ret << endl;
}
