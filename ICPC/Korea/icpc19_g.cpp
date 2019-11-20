#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;
const int MAXT = 270000;

int n;
int a[MAXN], b[MAXN];
int lo[MAXN], dp[MAXN];

struct seg{
	int tree[MAXT], lim;
	void init(int n){
		memset(tree, 0x3f, sizeof(tree));
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void upd(int x, int v){
		x += lim;
		tree[x] = min(tree[x], v);
		for(int i=x/2; i; i>>=1) tree[i] = min(tree[2*i], tree[2*i+1]);
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
}seg;


int main(){
	scanf("%*d %d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	for(int i=1; i<=n; i++) scanf("%d",&b[i]);
	lo[1] = 1;
	for(int i=2; i<=n; i++){
		if(b[i] != b[i-1]) lo[i] = i;
		else lo[i] = lo[i-1];
	}
	seg.init(n);
	for(int i=1; i<=n; i++){
		if(lo[i] == 1){
			dp[i] = 1;
		}
		else{
			int x = lo[i];
			int z = lo[x - 1];
			lint s = 2 * a[x-1] - a[i];
			lint e = 2 * a[x] - a[i];
			int l = lower_bound(a + 1, a + n + 1, s) - a;
			int r = upper_bound(a + 1, a + n + 1, e) - a;
			l = max(l, z);
			r = min(r, x) - 1;
			dp[i] = min(seg.query(l, r), seg.query(lo[i], i - 1)) + 1;
		}
		seg.upd(i, dp[i]);
	}
	printf("%d\n", seg.query(lo[n], n));
}
