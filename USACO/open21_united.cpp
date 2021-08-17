#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 200005;
const int MAXT = 530000;

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		for(int i = x; i < MAXN; i+=i&-i) tree[i] += v;
	}
	int query(int x){
		int ret = 0;
		for(int i = x; i; i -= i&-i) ret += tree[i];
		return ret;
	}
}bit;

int n;

struct seg{
	struct node{
		int activeSum;
		lint sum;
		int lazy;
		node operator+(const node &nd)const{
			return (node){activeSum + nd.activeSum, sum + nd.sum, 0};
		}
	}tree[MAXT];
	void lazydown(int p){
		for(int i = 2*p; i < 2*p+2; i++){
			tree[i].sum += tree[p].lazy * tree[i].activeSum;
			tree[i].lazy += tree[p].lazy;
		}
		tree[p].lazy = 0;
	}
	void activate(int x, int y, int s = 1, int e = n, int p = 1){
		if(s == e){
			tree[p] = {1, y, 0};
			return;
		}
		lazydown(p);
		int m = (s+e)/2;
		if(x <= m) activate(x, y, s, m, 2*p);
		else activate(x, y, m+1, e, 2*p+1);
		tree[p] = tree[2*p] + tree[2*p+1];
	}
	lint query(int s, int e, int ps = 1, int pe = n, int p = 1){
		if(e < ps || pe < s) return 0;
		if(s <= ps && pe <= e) return tree[p].sum;
		lazydown(p);
		int pm = (ps+pe)/2;
		return query(s, e, ps, pm, 2*p) + query(s, e, pm+1, pe, 2*p+1);
	}
	void add(int s, int e, int x, int ps = 1, int pe = n, int p = 1){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p].sum += tree[p].activeSum * x;
			tree[p].lazy += x;
			return;
		}
		lazydown(p);
		int pm = (ps+pe)/2;
		add(s, e, x, ps, pm, 2*p);
		add(s, e, x, pm+1, pe, 2*p+1);
		tree[p] = tree[2*p] + tree[2*p+1];
	}
}seg;


int b[MAXN], prv[MAXN], nxt[MAXN];
int lst[MAXN];
vector<int> active[MAXN];
vector<pi> rect[MAXN];

int main(){
	scanf("%d",&n);
	for(int i = 1; i <= n; i++){
		scanf("%d",&b[i]);
	}
	fill(lst, lst + n + 1, 0);
	for(int i = 1; i <= n; i++){
		prv[i] = lst[b[i]];
		lst[b[i]] = i;
	}
	fill(lst, lst + n + 1, n+1);
	for(int i = n; i; i--){
		nxt[i] = lst[b[i]];
		lst[b[i]] = i;
	}
	for(int i = 1; i <= n; i++){
		active[prv[i] + 1].push_back(i);
		rect[prv[i] + 1].emplace_back(i+1, +1);
		rect[prv[i] + 1].emplace_back(nxt[i], -1);
		rect[i].emplace_back(i+1, -1);
		rect[i].emplace_back(nxt[i], +1);
	}
	lint ret = 0;
	for(int i = 1; i <= n; i++){
		for(auto &j : active[i]){
			seg.activate(j, bit.query(j));
		}
		for(auto &[j, v] : rect[i]){
			bit.add(j, v);
			seg.add(j, n, v);
		}
		ret += seg.query(i, nxt[i] - 1);
	}
	cout << ret << endl;
}
