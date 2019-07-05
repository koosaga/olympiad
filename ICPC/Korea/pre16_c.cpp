#include <bits/stdc++.h>
using namespace std;
const int MAXN = 30050;
using lint = long long;
using pi = pair<int, int>;

struct seg{
	int sx, ex, sy, ey;
}a[MAXN];
int vis[MAXN];

int l;

int func(int sx, int ex, int sy, int ey){
	if(max(sx, sy) <= min(ex, ey)) return 0;
	if(ex < sy) return sy - ex;
	return sx - ey;
}

lint gdist(seg a, seg b){
	int dx = func(a.sx, a.ex, b.sx, b.ex);
	int dy = func(a.sy, a.ey, b.sy, b.ey);
	int ans = dx * dx + dy * dy;
	if(ans > l) return 1e18;
	return ans;
}

lint dist[MAXN];

int main(){
	int x, y, z;
	scanf("%*d %*d %d %d %d %d",&x,&y,&z,&l);
	memset(dist, 0x3f, sizeof(dist));
	vector<pi> t(x);
	for(int i=0; i<x; i++) scanf("%d %d",&t[i].first,&t[i].second);
	for(int i=0; i<x-1; i++) a[i] = {t[i].first, t[i+1].first, t[i].second, t[i+1].second};
	t.resize(y);
	for(int i=0; i<y; i++) scanf("%d %d",&t[i].first,&t[i].second);
	for(int i=0; i<y-1; i++) a[i+x-1] = {t[i].first, t[i+1].first, t[i].second, t[i+1].second};
	for(int i=x+y-2; i<x+y-2+z; i++) scanf("%d %d %d %d",&a[i].sx,&a[i].sy,&a[i].ex,&a[i].ey);
	int v = x - 1 + y - 1 + z;
	for(int i=0; i<v; i++){
		if(a[i].sx > a[i].ex) swap(a[i].sx, a[i].ex);
		if(a[i].sy > a[i].ey) swap(a[i].sy, a[i].ey);
	}
	for(int i=0; i<x-1; i++) dist[i] = 0;
	while(true){
		lint cur = 1e18;
		int pos = -1;
		for(int j=0; j<v; j++){
			if(!vis[j] && dist[j] < cur){
				cur = dist[j];
				pos = j;
			}
		}
		if(pos == -1){
			puts("-1");
			return 0;
		}
		vis[pos] = 1;
		if(x - 1 <= pos && pos < x - 1 + y - 1){
			if(cur > 1e17) cur = -1;
			cout << cur << endl;
			return 0;
		}
		for(int j=0; j<v; j++){
			if(!vis[j]){
				dist[j] = min(dist[j], dist[pos] + gdist(a[pos], a[j]));
			}
		}
	}
}
