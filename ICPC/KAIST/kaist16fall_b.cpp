#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;

int n, k;

struct node{
	int adj[10][10];
}tree[270000];

node merge(node &l, node &r){
	node ret;
	lint diff = 0, same = 0;
	for(int i=0; i<k; i++){
		diff += 1ll * l.adj[0][i] * r.adj[i][1] % mod;
		same += 1ll * l.adj[0][i] * r.adj[i][0] % mod;
	}
	diff %= mod;
	same %= mod;
	for(int i=0; i<k; i++){
		for(int j=0; j<k; j++){
			if(i == k-1 || j == k-1){
				lint tmp = 0;
				for(int m=0; m<k; m++){
					tmp += 1ll * l.adj[i][m] * r.adj[m][j] % mod;
				}
				ret.adj[i][j] = tmp % mod;
			}
			else{
				if(i == j) ret.adj[i][j] = same;
				else ret.adj[i][j] = diff;
			}
		}
	}
	return ret;
}

void kill_lef(node &l){
	for(int i=0; i<k; i++){
		l.adj[i][k-1] = 0;
	}
}

void kill_rig(node &r){
	for(int i=0; i<k; i++){
		r.adj[k-1][i] = 0;
	}
}

void init(int s, int e, int p){
	if(s+1 == e){
		for(int i=0; i<k; i++){
			for(int j=0; j<k; j++){
				tree[p].adj[i][j] = (i != j);
			}
		}
		return;
	}
	int m = (s+e)/2;
	init(s, m, 2*p);
	init(m, e, 2*p+1);
	tree[p] = merge(tree[2*p], tree[2*p+1]);
}

void update(int s, int e, int ps, int pe, int p, int c){
	if(e <= ps || pe <= s) return;
	if(ps + 1 == pe){
		if(pe == c) kill_lef(tree[p]);
		else kill_rig(tree[p]);
		return;
	}
	int pm = (ps+pe)/2;
	update(s, e, ps, pm, 2*p, c);
	update(s, e, pm, pe, 2*p+1, c);
	tree[p] = merge(tree[2*p], tree[2*p+1]);
}

int query(){
	lint ret = 0;
	for(int i=0; i<k; i++){
		for(int j=0; j<k; j++){
			if(i != j) ret += tree[1].adj[i][j];
		}
	}
	ret *= k;
	return ret % mod;
}

int main(){
	cin >> n >> k;
	if(n == 1){
		cout << 1ll * k * k << endl << 1ll * k * (k-1);
		return 0;
	}
	if(k == 1){
		for(int i=0; i<=n; i++) puts("0");
		return 0;
	}
	init(1, n, 1);
	printf("%d\n", query());
	for(int i=0; i<n; i++){
		int x;
		scanf("%d",&x);
		if(x == 1) update(1, 2, 1, n, 1, 1);
		else update(x-1, x, 1, n, 1, x);
		printf("%d\n", query());
	}
}
