#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int mod = 1e9 + 7;
const int inf = 1e9;
typedef pair<int, int> pi;
typedef long long lint;

struct pnt{
	int x, y, z; 
	bool operator<(const pnt &p)const{
		return pi(x, y) < pi(p.x, p.y);
	}
}a[MAXN], b[MAXN];

int n, m, ans[MAXN];
struct seg{
	lint tree[MAXN];
	void clear(){ fill(tree, tree + MAXN, -1e10); }
	void add(int x, lint v){
		while(x < MAXN){
			tree[x] = max(tree[x], v);
			x += x & -x;
		}
	}
	lint query(int x){
		lint ret = -1e10;
		while(x){
			ret = max(ret, tree[x]);
			x -= x & -x;
		}
		return ret;
	}
}seg;

void solve(){
	sort(a, a+n);
	sort(b, b+m);
	vector<int> v;
	seg.clear();
	v.push_back(-inf);
	for(int i=0; i<n; i++){
		v.push_back(a[i].y);
	}
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	int p = 0;
	for(int i=0; i<m; i++){
		while(p < n && a[p].x <= b[i].x){
			int l = lower_bound(v.begin(), v.end(), a[p].y) - v.begin();
			seg.add(l, 1ll * a[p].x + a[p].y - a[p].z); 
			p++;
		}
		int q = --upper_bound(v.begin(), v.end(), b[i].y) - v.begin();
		lint tmp = -seg.query(q) + b[i].x + b[i].y;
		if(ans[b[i].z] > tmp) ans[b[i].z] = tmp;
	}
}

void rx(){
	for(int i=0; i<n; i++) a[i].x = inf - a[i].x;
	for(int i=0; i<m; i++) b[i].x = inf - b[i].x;
}

void ry(){
	for(int i=0; i<n; i++) a[i].y = inf - a[i].y;
	for(int i=0; i<m; i++) b[i].y = inf - b[i].y;
}

int main(){
	freopen("slingshot.in", "r", stdin);
	freopen("slingshot.out", "w", stdout);
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		scanf("%d %d %d",&a[i].x,&a[i].y,&a[i].z);
	}
	for(int i=0; i<m; i++){
		scanf("%d %d",&b[i].x,&b[i].y);
		b[i].z = i;
		ans[i] = abs(b[i].y - b[i].x);	
	}
	solve();
	rx();
	solve();
	rx();
	ry();
	solve();
	rx();
	solve();
	for(int i=0; i<m; i++) printf("%d\n", ans[i]);
}
