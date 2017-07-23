#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

struct jaryo{
	map<int, int> mp;
	int offset = -200000000;
	void update(int dx){
		offset += dx;
	}
	int query(){
		int ret = 0;
		for(int i=-offset; i; i-=i&-i){
			if(mp.find(i) != mp.end()) ret += mp[i];
		}
		return ret;
	}
	void add(int x, int v){
		x -= offset;
		while(x <= 500000000){
			mp[x] += v;
			x += x & -x;
		}
	}
}jx0, jx1, jy0, jy1;

void add(jaryo &j, int s, int e){
	if(s > e) swap(s, e);
	j.add(s, 1);
	j.add(e, -1);
}

void rem(jaryo &j, int s, int e){
	if(s > e) swap(s, e);
	j.add(s, -1);
	j.add(e, 1);
}
char buf[4];
int n, q, x[100005], y[100005];

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d %d",&x[i],&y[i]);
	int p = 1, sx = 1, sy = 1;
	for(int i=1; i<=n; i++){
		if(i != 1) add(jx1, sx, sx + x[i]);
		if(i != 1) add(jy1, sy, sy + y[i]);
		sx += x[i];
		sy += y[i];
	}
	sx = sy = 1;
	scanf("%d",&q);
	while(q--){
		scanf("%s", buf);
		if(*buf == 'Q'){
			int ans = jx0.query() + jx1.query() + jy0.query() + jy1.query();
			if(1ll * sx * (sx + x[p]) < 0) ans++;
			if(1ll * sy * (sy + y[p]) < 0) ans++;
			printf("%d\n", ans);
		}
		if(*buf == 'B'){
			if(p == 1) continue;
			add(jx1, sx, sx + x[p]);
			add(jy1, sy, sy + y[p]);
			p--;
			sx -= x[p];
			sy -= y[p];
			rem(jx0, sx, sx + x[p]);
			rem(jy0, sy, sy + y[p]);
		}
		if(*buf == 'F'){
			if(p == n) continue;
			add(jx0, sx, sx + x[p]);
			add(jy0, sy, sy + y[p]);
			sx += x[p];
			sy += y[p];
			p++;
			rem(jx1, sx, sx + x[p]);
			rem(jy1, sy, sy + y[p]);
		}
		if(*buf == 'C'){
			int nx, ny;
			scanf("%d %d",&nx,&ny);
			jx1.update(nx - x[p]);
			jy1.update(ny - y[p]);
			x[p] = nx, y[p] = ny;
		}
	}
}
