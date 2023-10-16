// shirley smokes weed
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 500005;
const int MAXT = 530000;

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		for(int i=x+1; i<MAXN; i+=i&-i) tree[i] += v;
	}
	int query(int x){
		int ret = 0;
		for(int i=x+1; i; i-=i&-i) ret += tree[i];
		return ret;
	}
}bit;

struct seg{
	struct node{
		lint sum, pmin;
		node operator+(const node &n)const{
			return (node){sum + n.sum, min(pmin, sum + n.pmin)};
		}
	}tree[MAXT];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void upd(int x, int v){
		x += lim;
		tree[x] = (node){v, min(v, 0)};
		while(x > 1){
			x >>= 1;
			tree[x] = tree[2*x] + tree[2*x+1];
		}
	}
}seg;

int n, m, a[MAXN], b[MAXN], c[MAXN], sa[MAXN];

void Do(int x){
	if(x <= n) seg.upd(x, c[x] - sa[n + 1 - x]);
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	for(int i=1; i<=m; i++) scanf("%d",&b[i]);
	for(int i=1; i<=n; i++){
		sa[i] = a[i];
		bit.add(a[i], 1);
	}
	for(int i=1; i<=m; i++){
		c[b[i]]++;
	}
	for(int i=MAXN - 2; i >= 0; i--) c[i] += c[i + 1];
	sort(sa + 1, sa + n + 1);
	seg.init(n);
	for(int i=1; i<=n; i++) Do(i);
	int q; scanf("%d",&q);
	while(q--){
		int t, v; scanf("%d %d",&t,&v);
		if(t == 1){
			int pos = bit.query(a[v]);
			bit.add(a[v], -1);
			a[v]++;
			sa[pos]++;
			bit.add(a[v], +1);
			Do(n + 1 - pos);
		}
		if(t == 2){
			int pos = bit.query(a[v] - 1);
			bit.add(a[v], -1);
			a[v]--;
			sa[pos + 1]--;
			bit.add(a[v], +1);
			Do(n - pos);
		}
		if(t == 3){
			b[v]++;
			c[b[v]]++;
			Do(b[v]);
		}
		if(t == 4){
			c[b[v]]--;
			Do(b[v]);
			b[v]--;
		}
		printf("%d\n", seg.tree[1].pmin >= 0);
	}
}

