#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
typedef vector<int> vi;

int n;
int a[200005], b[200005];
int c[200005], d[200005];
stack<int> S[200005];

struct seg{
	struct node{
		int sum, pref;
	}tree[1050000];
	int lim;
	node merge(node l, node r){
		return (node){l.sum + r.sum, max(l.pref, l.sum + r.pref)};
	}
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void add(int x, int v){
		x += lim;
		tree[x].sum += v;
		tree[x].pref = max(tree[x].sum, 0);
		while(x > 1){
			x >>= 1;
			tree[x] = merge(tree[2*x], tree[2*x+1]);
		}
	}
	int query(){
		return tree[1].pref > 0;
	}
}seg;

int matchable(int x, int y){
	seg.add(b[x], 1);
	seg.add(d[y],-1);
	if(seg.query()){
		seg.add(b[x], -1);
		seg.add(d[y], 1);
		return 0;
	}
	return 1;
}

int main(){
	scanf("%d",&n);
	vector<int> vx;
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i],&b[i]);
		vx.push_back(b[i]);
	}
	for(int i=0; i<n; i++){
		scanf("%d %d",&c[i],&d[i]);
		vx.push_back(d[i]);
	}
	sort(vx.begin(), vx.end());
	vx.erase(unique(vx.begin(), vx.end()), vx.end());
	seg.init(vx.size());
	for(int i=0; i<n; i++){
		b[i] = lower_bound(vx.begin(), vx.end(), b[i]) - vx.begin();
		d[i] = lower_bound(vx.begin(), vx.end(), d[i]) - vx.begin();
		seg.add(b[i], -1);
		seg.add(d[i], 1);
	}
	int p = 0, cnt = 0, popped = 0;
	for(int i=0; i<n; i++){
		while(p < n && d[p] >= b[i]){
			S[c[p]].push(p);
			p++;
		}
		if(S[a[i]].size() && matchable(i, S[a[i]].top())){
			S[a[i]].pop();
		}
		else{
			cnt++;
		}
	}
	cout << cnt << endl;
}
