#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 2005;

int n, m;
int a[MAXN][MAXN];

int choice(int x, int y){
	int le = a[x][(y + m - 1) % m];
	int mi = a[x][y];
	int ri = a[x][(y + 1) % m];
	int maxv = max({le, mi, ri});
	if(maxv == le) return -1;
	if(maxv == ri) return 1;
	return 0;
}

int nxt[30][MAXN];

struct seg{
	int tree[4100][MAXN], lim;
	void merge(int p){
		for(int i=0; i<m; i++){
			tree[p][i] = tree[2*p+1][tree[2*p][i]];
		}
	}
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				tree[i + lim][j] = (j + choice(i, j) + m) % m;
			}
		}
		for(int i=n; i<lim; i++){
			iota(tree[i + lim], tree[i + lim] + m, 0);
		}
		for(int i=lim-1; i; i--) merge(i);
	}
	void upd(int x){
		for(int j=0; j<m; j++) tree[x + lim][j] = (j + choice(x, j) + m) % m;
		x += lim;
		while(x > 1){
			x >>= 1;
			merge(x);
		}
	}
}seg;

void build(){
	for(int i=0; i<m; i++) nxt[0][i] = seg.tree[1][i];
	for(int i=1; i<30; i++){
		for(int j=0; j<m; j++) nxt[i][j] = nxt[i-1][nxt[i-1][j]];
	}
}

int round_trip(int x, int y){
	for(int i=0; i<30; i++){
		if((y >> i) & 1) x = nxt[i][x];
	}
	return x;
}

void print(int &x, int &y){
	x = (x + n - 1) % n;
	printf("%d %d\n", y+1, x+1);
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			scanf("%d",&a[j][i]);
		}
	}
	swap(n, m);
	seg.init(n);
	build();
	int q;
	scanf("%d",&q);
	int px = 0, py = 0;
	while(q--){
		char buf[20];
		scanf("%s", buf);
		if(*buf == 'm'){
			int k;
			scanf("%d",&k);
			px = (px + 1) % n;
			while(px != 0 && k > 0){
				py = (py + choice(px, py) + m) % m;
				px = (px + 1) % n;
				k--;
			}
			py = round_trip(py, k / n);
			k %= n;
			while(k > 0){
				py = (py + choice(px, py) + m) % m;
				px = (px + 1) % n;
				k--;
			}
			print(px, py);
		}
		else{
			int x, y, z;
			scanf("%d %d %d",&x,&y,&z);
			x--, y--;
			swap(x, y);
			a[x][y] = z;
			seg.upd(x);
			build();
		}
	}
}
