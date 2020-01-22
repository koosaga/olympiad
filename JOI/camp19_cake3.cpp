#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 200005;
const int MAXT = 4000005;

struct node{
	int l, r;
	int cnt;
	lint sum;
}tree[MAXT];
int piv;

int newnode(){ return ++piv; }

void init(int s, int e, int p){
	if(s == e) return;
	int m = (s+e)/2;
	tree[p].l = newnode();
	tree[p].r = newnode();
	init(s, m, tree[p].l);
	init(m+1, e, tree[p].r);
}

void upd(int pos, int s, int e, int val, int prv, int nxt){
	if(s == e){
		tree[nxt].cnt = tree[prv].cnt + 1;
		tree[nxt].sum = tree[prv].sum + val;
		return;
	}
	int m = (s+e)/2;
	if(pos <= m){
		tree[nxt].l = newnode();
		tree[nxt].r = tree[prv].r;
		upd(pos, s, m, val, tree[prv].l, tree[nxt].l);
	}
	else{
		tree[nxt].l = tree[prv].l;
		tree[nxt].r = newnode();
		upd(pos, m+1, e, val, tree[prv].r, tree[nxt].r);
	}
	tree[nxt].cnt = tree[tree[nxt].l].cnt + tree[tree[nxt].r].cnt;
	tree[nxt].sum = tree[tree[nxt].l].sum + tree[tree[nxt].r].sum;	
}

lint query(int s, int e, int k, int r1, int r2){
	if(s == e){
		if(k == 0) return 0;
		int tot = tree[r2].cnt - tree[r1].cnt;
		return (1ll * k * (tree[r2].sum - tree[r1].sum)) / tot;
	}
	int m = (s+e)/2;
	int subcnt = tree[tree[r2].l].cnt - tree[tree[r1].l].cnt;
	if(subcnt > k){
		return query(s, m, k, tree[r1].l, tree[r2].l);
	}
	else{
		return tree[tree[r2].l].sum - tree[tree[r1].l].sum + 
		query(m+1, e, k - subcnt, tree[r1].r, tree[r2].r);
	}
}

int n, m;
int root[MAXN];
pi a[MAXN];
vector<int> v;

lint cost(int l, int r){
	if(r - l + 1 < m) return -1e18;
	return query(0, sz(v) - 1, m, root[l], root[r + 1]) - 2ll * (a[r].first - a[l].first);
}

lint solve(int s, int e, int ps, int pe){
	if(s > e) return -1e18;
	int m = (s+e)/2;
	lint optv = -2e18;
	int optc = -1;
	for(int i=max(ps, m); i<=pe; i++){
		lint tmp = cost(m, i);
		if(optv < tmp){
			optv = tmp;
			optc = i;
		}
	}
	return max({solve(s, m - 1, ps, optc), solve(m + 1, e, optc, pe), optv});
}


int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].second,&a[i].first);
		v.push_back(-a[i].second);
	}
	sort(all(v));
	v.resize(unique(all(v)) - v.begin());
	sort(a, a + n);
	root[0] = newnode();
	init(0, sz(v) - 1, root[0]);
	for(int i=0; i<n; i++){
		root[i + 1] = newnode();
		int pos = lower_bound(all(v), -a[i].second) - v.begin();
		upd(pos, 0, sz(v) - 1, a[i].second, root[i], root[i + 1]);
	}
	cout << solve(0, n - m, 0, n - 1) << endl;
}
