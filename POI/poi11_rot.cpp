#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
const int MAXN = 200005;

int n;

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		while(x <= n){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x) ret += tree[x], x -= x & -x;
		return ret;
	}
}bit;

int cnt, node;
int l[2 * MAXN], r[2 * MAXN];
int st[2 * MAXN], ed[2 * MAXN];
int a[MAXN];

void read_tree(int v){
	int x;
	scanf("%d",&x);
	st[v] = cnt;
	if(x == 0){
		l[v] = ++node;
		read_tree(node);
		r[v] = ++node;
		read_tree(node);
	}
	else{
		a[cnt++] = x;
	}
	ed[v] = cnt;
}

lint dfs(int v){
	if(ed[v] - st[v] == 1){
		bit.add(a[st[v]], 1);
		return 0;
	}
	int ls = ed[l[v]] - st[l[v]];
	int rs = ed[r[v]] - st[r[v]];
	lint ans1 = 0, ans2 = 0;
	if(ls < rs){
		ans1 += dfs(l[v]);
		for(int i=st[l[v]]; i<ed[l[v]]; i++){
			bit.add(a[i], -1);
		}
		ans1 += dfs(r[v]);
		for(int i=st[l[v]]; i<ed[l[v]]; i++){
			ans2 += bit.query(a[i]);
		}
		for(int i=st[l[v]]; i<ed[l[v]]; i++){
			bit.add(a[i], 1);
		}
	}
	else{
		ans1 += dfs(r[v]);
		for(int i=st[r[v]]; i<ed[r[v]]; i++){
			bit.add(a[i], -1);
		}
		ans1 += dfs(l[v]);
		for(int i=st[r[v]]; i<ed[r[v]]; i++){
			ans2 += ls - bit.query(a[i]);
		}
		for(int i=st[r[v]]; i<ed[r[v]]; i++){
			bit.add(a[i], 1);
		}
	}
	return ans1 + min(1ll * ls * rs - ans2, ans2);
}

int main(){
	scanf("%d",&n);
	read_tree(0);
	printf("%lld",dfs(0));
}
