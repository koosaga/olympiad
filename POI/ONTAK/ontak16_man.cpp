#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;

struct seg{
	int tree[530000], lim;
	void init(){
		memset(tree, 0x3f, sizeof(tree));
		lim = (1<<18);
	}
	void add(int x, int v){
		x += lim;
		tree[x] = min(tree[x], v);
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
	void clear(int x){
		x += lim;
		tree[x] = 1e9;
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
	int query(int s, int e){
		s += lim;
		e += lim;
		int ret = 1e9;
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
int t[200005], x[200005], y[200005];
int ans[200005];

struct query{
	int x, y, idx;
	bool operator<(const query &q)const{
		return pi(x, y) < pi(q.x, q.y);
	}
};

void solve(int s, int e){
	if(s == e) return;
	int m = (s+e)/2;
	solve(s, m);
	solve(m+1, e);
	vector<pi> ins;
	vector<query> qry;
	for(int i=s; i<=m; i++){
		if(t[i] == 1) ins.push_back(pi(x[i], y[i]));
	}
	for(int i=m+1; i<=e; i++){
		if(t[i] == 2) qry.push_back({x[i], y[i], i});
	}
	sort(ins.begin(), ins.end());
	sort(qry.begin(), qry.end());
	int p = 0;
	for(auto &i : qry){
		while(p < ins.size() && ins[p] <= pi(i.x, i.y)){
			seg1.add(ins[p].second, -ins[p].first + ins[p].second);
			seg2.add(ins[p].second, -ins[p].first - ins[p].second);
			p++;
		}
		ans[i.idx] = min(ans[i.idx], i.x - i.y + seg1.query(i.y, 200000));
		ans[i.idx] = min(ans[i.idx], i.x + i.y + seg2.query(1, i.y));
	}
	while(p > 0){
		p--;
		seg1.clear(ins[p].second);
		seg2.clear(ins[p].second);
	}
	reverse(ins.begin(), ins.end());
	reverse(qry.begin(), qry.end());
	p = 0;
	for(auto &i : qry){
		while(p < ins.size() && ins[p] > pi(i.x, i.y)){
			seg1.add(ins[p].second, ins[p].first + ins[p].second);
			seg2.add(ins[p].second, ins[p].first - ins[p].second);
			p++;
		}
		ans[i.idx] = min(ans[i.idx], -i.x - i.y + seg1.query(i.y, 200000));
		ans[i.idx] = min(ans[i.idx], -i.x + i.y + seg2.query(1, i.y));
	}
	while(p > 0){
		p--;
		seg1.clear(ins[p].second);
		seg2.clear(ins[p].second);
	}
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d %d",&t[i],&x[i],&y[i]);
	}
	memset(ans, 0x3f, sizeof(ans));
	seg1.init();
	seg2.init();
	solve(0, n-1);
	for(int i=0; i<n; i++){
		if(t[i] == 2) printf("%d\n", ans[i]);
	}
}
