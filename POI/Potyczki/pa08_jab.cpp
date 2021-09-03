#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

struct seg{
	lint tree[270000], lim;
	void init(int n){
		memset(tree, 0x3f, sizeof(tree));
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void add(int x, lint v){
		x += lim;
		tree[x] = min(tree[x], v);
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
	void clear(int x){
		x += lim;
		tree[x] = 1e18;
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
	lint query(int s, int e){
		s += lim;
		e += lim;
		lint ret = 1e18;
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}seg1, seg2;

int n;
lint ans[100005];

struct query{
	int x, y, idx;
	bool operator<(const query &q)const{
		return pi(x, y) < pi(q.x, q.y);
	}
};

int main(){
	memset(ans, 0x3f, sizeof(ans));
	vector<pi> ins;
	vector<query> qry;
	vector<int> vy;
	int n, q;
	scanf("%d",&n);
	scanf("%d",&q);
	for(int i=0; i<n; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		ins.push_back(pi(x, y));
		vy.push_back(y);
	}
	sort(vy.begin(), vy.end());
	vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
	for(int i=0; i<q; i++){
		int x, y, idx;
		scanf("%d %d",&x,&y);
		idx = i;
		qry.push_back({x, y, idx});
	}
	sort(ins.begin(), ins.end());
	sort(qry.begin(), qry.end());
	int p = 0;
	seg1.init(n);
	seg2.init(n);
	for(auto &i : qry){
		while(p < ins.size() && ins[p] <= pi(i.x, i.y)){
			auto lbnd = lower_bound(vy.begin(), vy.end(), ins[p].second)
				- vy.begin();
			seg1.add(lbnd, -ins[p].first + ins[p].second);
			seg2.add(lbnd, -ins[p].first - ins[p].second);
			p++;
		}
		auto lbnd = lower_bound(vy.begin(), vy.end(), i.y) - vy.begin();
		ans[i.idx] = min(ans[i.idx], i.x - i.y + seg1.query(lbnd, vy.size()-1));
		ans[i.idx] = min(ans[i.idx], i.x + i.y + seg2.query(0, lbnd-1));
	}
	seg1.init(n);
	seg2.init(n);
	reverse(ins.begin(), ins.end());
	reverse(qry.begin(), qry.end());
	p = 0;
	for(auto &i : qry){
		while(p < ins.size() && ins[p] > pi(i.x, i.y)){
			auto lbnd = lower_bound(vy.begin(), vy.end(), ins[p].second)
				- vy.begin();
			seg1.add(lbnd, ins[p].first + ins[p].second);
			seg2.add(lbnd, ins[p].first - ins[p].second);
			p++;
		}
		auto lbnd = lower_bound(vy.begin(), vy.end(), i.y) - vy.begin();
		ans[i.idx] = min(ans[i.idx], -i.x - i.y + seg1.query(lbnd, vy.size()-1));
		ans[i.idx] = min(ans[i.idx], -i.x + i.y + seg2.query(0, lbnd-1));
	}
	printf("%lld\n", *min_element(ans, ans + q));
}
