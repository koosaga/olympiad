#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 300005;

static char buf[1 << 19]; // size : any number geq than 1024
static int idx = 0;
static int bytes = 0;
static inline int _read() {
    if (!bytes || idx == bytes) {
        bytes = (int)fread(buf, sizeof(buf[0]), sizeof(buf), stdin);
        idx = 0;
    }
    return buf[idx++];
}
static inline int _readInt() {
    int x = 0, s = 1;
    int c = _read();
    while (c <= 32) c = _read();
    if (c == '-') s = -1, c = _read();
    while (c > 32) x = 10 * x + (c - '0'), c = _read();
    if (s < 0) x = -x;
    return x;
}


int n, m;

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		while(x < MAXN){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		lint ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

int ipow(int x, int p){
	if(p == 0) return 1;
	if(p == 1) return x;
	if(p & 1) return 1ll * ipow(1ll * x * x % m, p / 2) * x % m;
	return ipow(1ll * x * x % m, p / 2);
}

struct seg{
	int cnt[MAXN];
	int tree[1050000], lim = (1<<19);
	void init(){
		fill(tree, tree + 1050000, 1);
	}
	void add(int x, int v){
		cnt[x] += v;
		if(v == 0) return;
		if(v > 0) tree[x + lim] = 1ll * tree[x + lim] * ipow(x, v) % m;
		else tree[x + lim] = ipow(x, cnt[x]);
		x += lim;
		while(x > 1){
			x >>= 1;
			tree[x] = 1ll * tree[2*x] * tree[2*x+1] % m;
		}
	}
}seg;

int a[MAXN];
int che[MAXN];
int occ[MAXN];
int cut[MAXN];

vector<int> cnd;

void constantcut(){
	for(auto &i : cnd){
		if(cut[i]) seg.add(i, cut[i]);
		cut[i] = 0;
	}
	cnd.clear();
}

void add_num(int x, int v){
	while(x != 1){
		int cnt = 0, cv = che[x];
		while(che[x] == cv) x /= cv, cnt++;
		cut[cv] += v * cnt;
		cnd.push_back(cv);
	}
}

int main(){
	n = _readInt();
	m = _readInt();
	for(int i=2; i<MAXN; i++){
		for(int j=i; j<MAXN; j+=i){
			if(!che[j]) che[j] = i;
		}
	}
	for(int i=1; i<=n; i++){
		a[i] = _readInt();
		occ[a[i]]++;
	}
	for(int i=1; i<=n; i++) add_num(i, 1);
	for(int i=1; i<MAXN; i++){
		for(int j=1; j<=occ[i]; j++){
			add_num(j, -1);
		}
	}
	seg.init();
	for(int i=1; i<MAXN; i++){
		if(occ[i]) bit.add(i, occ[i]);
	}
	constantcut();
	lint ans = 1;
	for(int i=1; i<=n; i++){
		int occSum = bit.query(a[i] - 1);
		if(occSum != 0){
			add_num(occSum, 1);
			add_num(n - i + 1, -1);
			constantcut();
			ans += seg.tree[1];
			add_num(occ[a[i]], 1);
			add_num(occSum, -1);
		}
		else{
			add_num(occ[a[i]], 1);
			add_num(n - i + 1, -1);
		}
		occ[a[i]]--;
		bit.add(a[i], -1);
	}
	ans %= m;
	cout << ans << endl;
}

