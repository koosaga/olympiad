#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 200005;
 
int n, l[MAXN], r[MAXN], cost[MAXN];
pi a[MAXN];
int ret[MAXN];
 
struct bit{
	int tree[MAXN];
	void add(int x, int v){
		for(int i=x; i<MAXN; i+=i&-i) tree[i] += v;
	}
	int query(int x){
		int ret = 0;
		for(int i=x; i; i-=i&-i) ret += tree[i];
		return ret;
	}
}bit;
 
struct point{
	int x, y, z;
	bool operator<(const point &p)const{
		return x < p.x;
	}
};
 
struct event{
	int pos, s, e, idx;
	bool operator<(const event &e)const{
		return pos < e.pos;
	}
};
 
vector<point> w;
vector<event> ev;
 
int main(){
	vector<int> crd;
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		int v;
		scanf("%d %d %d",&l[i],&r[i],&v);
		a[i] = pi(v, v);
		crd.push_back(v);
	}
	sort(all(crd));
	for(int i=n; i; i--){
		a[i].first = lower_bound(all(crd), a[i].first) - crd.begin() + 1;
		a[i].second = a[i].first;
		if(l[i]) a[i].first = min(a[i].first, a[l[i]].first), cost[i]++;
		if(r[i]) a[i].second = max(a[i].second, a[r[i]].second), cost[i]++;
		cost[i] = 2;
		w.push_back({a[i].second, a[i].first, cost[i]});
	}
	auto add = [&](int s, int e, int idx){
		s = lower_bound(all(crd), s) - crd.begin() + 1;
		e = upper_bound(all(crd), e) - crd.begin();
		if(s <= e) ev.push_back({e, s, e, idx});
	};
	int q; scanf("%d",&q);
	for(int i=0; i<q; i++){
		int l, r;
		scanf("%d %d",&l,&r);
		ret[i] = 2*n+1;
		add(l, r, i);
		add(-2e9, l-1, i);
		add(r+1, 2e9, i);
	}
	sort(all(w));
	sort(all(ev));
	int j = 0;
	for(auto &i : ev){
		while(j < sz(w) && w[j].x <= i.pos){
			bit.add(w[j].y, w[j].z);
			j++;
		}
		ret[i.idx] -= (bit.query(i.e) - bit.query(i.s - 1));
	}
	for(int i=0; i<q; i++) printf("%d\n", ret[i]);
}
