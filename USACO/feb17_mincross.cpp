#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;

int n, k;
int a[100005], b[100005], p[100005];

struct bit{
	int tree[100005];
	void init(){
		memset(tree, 0, sizeof(tree));
	}
	void add(int x, int v){
		while(x <= n){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

lint solve(){
	lint inv = 0;
	bit.init();
	for(int i=1; i<=n; i++){
		inv += bit.query(n) - bit.query(p[i]);
		bit.add(p[i], 1);
	}
	bit.init();
	lint ret = inv, tmp = 0;
	for(int i=1; i<n; i++){
		tmp -= bit.query(n) - bit.query(p[i]);
		tmp += p[i] - 1 - bit.query(p[i] - 1);
		lint chg = 2 * tmp - 1ll * i * (n-i);
		ret = min(ret, inv - chg);
		bit.add(p[i], 1);
	}
	return ret;
}

int main(){
	freopen("mincross.in", "r", stdin);
	freopen("mincross.out", "w", stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		int x;
		scanf("%d",&x);
		a[x] = i;
	}
	for(int i=1; i<=n; i++){
		int x;
		scanf("%d",&x);
		b[x] = i;
	}
	for(int i=1; i<=n; i++){
		p[a[i]] = b[i];
	}
	lint ret = solve();
	for(int i=1; i<=n; i++){
		p[b[i]] = a[i];
	}
	ret = min(ret, solve());
	cout << ret;
}
