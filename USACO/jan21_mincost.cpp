#include <bits/stdc++.h>
using namespace std;
const int MAXN = 750005;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

__int128 ccw(pi a, pi b, pi c){
	__int128 dx1 = b.first - a.first;
	__int128 dy1 = b.second - a.second;
	__int128 dx2 = c.first - a.first;
	__int128 dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}

int n, m;
int minProfitPoint(pi p1){
	lint s = 1, e = n;
	while(s != e){
		lint m = (s+e+1)/2;
		pi p2 = pi(1, 2 * m - 1);
		if(ccw(pi(0, 0), p1, p2) >= 0) e = m - 1;
		else s = m;
	}
	return s;
}
 
lint par[MAXN], a[MAXN], xth[MAXN];
int spt[20][MAXN];
lint ktx[MAXN];

int main(){
	scanf("%d %d",&n,&m);
	vector<pi> bh;
	xth[1] = 1;
	for(int i=1; i<=m; i++){
		int z; scanf("%d",&z);
		a[i] = z;
		while(bh.size() >= 2 && ccw(bh[bh.size() - 2], bh.back(), pi(i, z)) <= 0){
			bh.pop_back();
		}
		if(sz(bh)){
			par[i] = bh.back().first;
			xth[i] = minProfitPoint(pi(i - par[i], a[i] - a[par[i]]));
		}
		bh.emplace_back(i, z);
		if(i > 1){
			ktx[i] = ktx[par[i]] + 1ll * xth[i] * xth[i] * (i - par[i]) + (xth[i] - xth[par[i]]) * a[par[i]];
		}
	}
	spt[0][1] = 1;
	for(int i=2; i<=m; i++) spt[0][i] = par[i];
	for(int i=1; i<20; i++){
		for(int j=1; j<=m; j++){
			spt[i][j] = spt[i-1][spt[i-1][j]];
		}
	}
	int q; scanf("%d",&q);
	while(q--){
		int x, y; scanf("%d %d",&x,&y);
		lint ret = 0;
		int parent_y = y;
		for(int i = 19; i >= 0; i--){
			if(xth[spt[i][parent_y]] > x){
				parent_y = spt[i][parent_y];
			}
		}
		while(xth[parent_y] > x) parent_y = par[parent_y];
		ret += 1ll * x * x * (y - parent_y);
		y = parent_y;
		ret += 1ll * (x - xth[y]) * a[y] + ktx[y];
		printf("%lld\n", ret);
	}
}
