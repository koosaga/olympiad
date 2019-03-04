#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int MAXT = 270000;
typedef long long lint;
typedef pair<int, int> pi;

int n, q;
int px[MAXN], nx[MAXN], py[MAXN], ny[MAXN];

struct seg{
	pi tree[17][MAXN];
	int lg[MAXN];
	void init(int n, int *a){
		int p = 0;
		for(int i=1; i<=n; i++){
			while((2 << p) <= i) p++;
			lg[i] = p;
		}
		for(int i=1; i<=n; i++) tree[0][i] = pi(a[i], i);
		for(int i=1; i<17; i++){
			for(int j=1; j<=n; j++){
				tree[i][j] = tree[i-1][j];
				if(j + (1<<(i-1)) <= n) tree[i][j] = max(tree[i][j], tree[i-1][j +(1<<(i-1))]);
			}
		}
	}
	pi query(int s, int e){
		if(s > e) return pi(-2e9, -1);
		int l = lg[e-s+1];
		return max(tree[l][s], tree[l][e-(1<<l)+1]);
	}
}segpx, segnx, segpy, segny;

int main(){
	scanf("%d %d",&n,&q);
	for(int i=1; i<=n; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		px[i] = x;
		nx[i] = -x;
		py[i] = y;
		ny[i] = -y;
	}
	segpx.init(n, px);
	segnx.init(n, nx);
	segpy.init(n, py);
	segny.init(n, ny);
	while(q--){
		int l, r;
		scanf("%d %d",&l,&r);
		vector<int> v;
		v.push_back(segpx.query(l, r).second);
		v.push_back(segnx.query(l, r).second);
		v.push_back(segpy.query(l, r).second);
		v.push_back(segny.query(l, r).second);
		int ans = 2e9 + 100;
		for(auto &i : v){
			int maxx = max(segpx.query(l, i - 1), segpx.query(i + 1, r)).first;
			int minx = -max(segnx.query(l, i - 1), segnx.query(i + 1, r)).first;
			int maxy = max(segpy.query(l, i - 1), segpy.query(i + 1, r)).first;
			int miny = -max(segny.query(l, i - 1), segny.query(i + 1, r)).first;
			ans = min(ans, max(maxx - minx, maxy - miny));
		}
		printf("%d\n", ans);
	}
}
