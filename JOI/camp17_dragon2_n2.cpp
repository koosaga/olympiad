#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

struct pnt{
	int x, y, c;
	int r1, r2;
}a[30005], s, e;

lint ccw(pnt a, pnt b, pnt c){
	return 1ll * (b.x - a.x) * (c.y - a.y) - 1ll * (c.x - a.x) * (b.y - a.y);
}

int n, m;
int stx[30005], sty[30005], edx[30005], edy[30005];

void label1(){
	sort(a, a+n, [&](const pnt &p, const pnt &q){
		bool bh1 = ccw(s, e, p) > 0;
		bool bh2 = ccw(s, e, q) > 0;
		if(bh1 != bh2) return bh1 > bh2;
		return ccw(s, p, q) > 0;
	});
	int dv = 0;
	for(int i=0; i<n; i++){
		a[i].r1 = i;
		if(ccw(s, e, a[i]) > 0) dv = i+1;
	}
	int p = 0;
	for(int i=dv; i<n; i++){
		while(p < dv && ccw(s, a[i], a[p]) > 0) p++;
		stx[i] = i;
		edx[i] = p;
	}
	p = dv;
	for(int i=0; i<dv; i++){
		while(p < n && ccw(s, a[i], a[p]) > 0) p++;
		stx[i] = p;
		edx[i] = i;
	}
}

void label2(){
	sort(a, a+n, [&](const pnt &p, const pnt &q){
		bool bh1 = ccw(s, e, p) > 0;
		bool bh2 = ccw(s, e, q) > 0;
		if(bh1 != bh2) return bh1 > bh2;
		return ccw(e, p, q) > 0;
	});
	int dv = 0;
	for(int i=0; i<n; i++){
		a[i].r2 = i;
		if(ccw(s, e, a[i]) > 0) dv = i+1;
	}
	int p = 0;
	for(int i=dv; i<n; i++){
		while(p < dv && ccw(e, a[i], a[p]) > 0) p++;
		sty[i] = p;
		edy[i] = i;
	}
	p = dv;
	for(int i=0; i<dv; i++){
		while(p < n && ccw(e, a[i], a[p]) > 0) p++;
		sty[i] = i;
		edy[i] = p;
	}
}

vector<pi> grp[30005];
map<pi, int> mp;

int query(int x, int y){
	if(mp.find(pi(x, y)) != mp.end()) return mp[pi(x, y)];
	int ret = 0;
	for(auto &i : grp[x]){
		for(auto &j : grp[y]){
			bool xma = !(edx[i.first] <= j.first && j.first < stx[i.first]);
			bool yma = (sty[i.second] <= j.second && j.second < edy[i.second]);
			if(xma && yma) ret++;
		}
	}
	mp[pi(x, y)] = ret;
	return ret;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		scanf("%d %d %d",&a[i].x,&a[i].y,&a[i].c);
	}
	scanf("%d %d %d %d",&s.x,&s.y,&e.x,&e.y);
	label1();
	label2();
	for(int i=0; i<n; i++){
		grp[a[i].c].push_back(pi(a[i].r1, a[i].r2));
	}
	int q;
	scanf("%d",&q);
	while(q--){
		int x, y;
		scanf("%d %d",&x,&y);
		printf("%d\n", query(x, y));
	}
}
