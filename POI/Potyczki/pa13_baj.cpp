#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 1000005;
 
int n;
int a[MAXN], b[MAXN], d[MAXN];
int ptr[MAXN], l[MAXN];
 
struct seg{
	int tree[2100000], lim;
	void init(int n){
		fill(tree, tree + 2100000, -2e9);
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void upd(int x, int v){
		x += lim;
		tree[x] = v;
		while(x > 1){
			x >>= 1;
			tree[x] = max(tree[2*x], tree[2*x+1]);
		}
	}
	int query(int s, int e){
		s += lim; e += lim;
		int ret = -2e9;
		while(s < e){
			if(s%2 == 1) ret = max(ret, tree[s++]);
			if(e%2 == 0) ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = max(ret, tree[s]);
		return ret;
	}
}seg1, seg2;

int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++) scanf("%d",&a[i]);
	for(int i=1; i<n; i++) scanf("%d",&b[i]);
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	memset(d, 0x3f, sizeof(d));
	d[0] = 0;
	for(int i=1; i<n; i++){
		d[i] = b[i];
		pq.push(pi(d[i], i));
	}
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(d[x.second] != x.first) continue;
		int i = x.second;
		int nxt = i % (n-1) + 1;
		if(d[nxt] > d[i] + a[i]){
			d[nxt] = d[i] + a[i];
			pq.push(pi(d[nxt], nxt));
		}
		int prv = (i == 1 ? (n-1) : (i-1));
		if(d[prv] > d[i] + a[prv]){
			d[prv] = d[i] + a[prv];
			pq.push(pi(d[prv], prv));
		}
	}
	int ans = 0;
	for(int i=n; i<2*n-1; i++){
		a[i] = a[i-n+1];
		d[i] = d[i-n+1];
		ans = max(ans, d[i]);
	}
	for(int i=1; i<2*n-1; i++) a[i] += a[i-1];
	int p = a[n-1];
	vector<pi> v;
	for(int i=0; i<2*n-2; i++){
		v.push_back(pi(a[i] - d[i+1], i));
	}
	sort(v.begin(), v.end());
	for(int i=0; i<2*n-2; i++){
		ptr[i] = lower_bound(v.begin(), v.end(), pi(a[i] - d[i+1], i)) - v.begin();
	}
	for(int i=0; i<n-1; i++){
		if(i > 0) l[i] = l[i-1];
		while(a[l[i] + 1] - a[i] <= p / 2) l[i]++;
	}
	seg1.init(2*n);
	seg2.init(2*n);
	for(int i=0; i<n-1; i++){
		for(int j=(i ? l[i-1] : -1) + 1; j<=l[i]; j++){
			seg1.upd(ptr[j], a[j]);
			seg2.upd(ptr[j], d[j+1]);
		}
		seg1.upd(ptr[i], 0);
		seg2.upd(ptr[i], 0);
		auto l = upper_bound(v.begin(), v.end(), pi(a[i] + d[i+1], i)) - v.begin();
		ans = max(ans, seg1.query(0, l - 1) - a[i]);
		ans = max(ans, seg2.query(l, 2*n - 1) + d[i+1]);
	}
	cout << ans << endl;
}