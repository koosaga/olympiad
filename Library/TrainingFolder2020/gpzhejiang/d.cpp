#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 200005;
const int MAXT = 40000005;

struct node{
	int son[4];
	lint add;
}tree[MAXT];

int piv;
int n;

struct rect{
	int sx, ex, sy, ey;
	rect(){}
	rect(int sx, int ex, int sy, int ey): sx(sx), ex(ex), sy(sy), ey(ey) {}
	rect xl(){ return rect(sx, (sx+ex)/2, sy, ey); }
	rect xr(){ return rect((sx+ex)/2+1, ex, sy, ey); }
	rect yl(){ return rect(sx, ex, sy, (sy+ey)/2); }
	rect yr(){ return rect(sx, ex, (sy+ey)/2+1, ey); }
	bool contain(rect &r){
		return sx <= r.sx && r.ex <= ex && sy <= r.sy && r.ey <= ey;
	}
	bool disjoint(rect &r){
		return r.ex < sx || ex < r.sx || r.ey < sy || ey < r.sy;
	}
	bool xinsec(rect &r){
		return max(sx, r.sx) <= min(ex, r.ex);
	}
	bool yinsec(rect &r){
		return max(sy, r.sy) <= min(ey, r.ey);
	}
	bool insec(rect &r){
		return xinsec(r) && yinsec(r);
	}

};

struct hasher {
    size_t operator()(const rect &r)const{ return (lint(r.sx) << 48) | (lint(r.ex) << 32) | (r.sy << 16) | (r.ey); }
};

map<rect, int> mp;
set<int> vis;

void add(int v, rect r, rect pr = rect(1, n, 1, n), int p = 0){
	if(r.disjoint(pr)) return;
	if(r.contain(pr)){
		tree[p].add += v;
		return;
	}
	if(vis.find(p) != vis.end()) return;
	vis.insert(p);
	if(r.xinsec(pr)){
		if(mp[pr.xl()] == mp.end()) mp[pr.xl()] = ++piv;
		if(mp[pr.xr()] == mp.end()) mp[pr.xr()] = ++piv;
		tree[p].son[0] = mp[pr.xl()];
		tree[p].son[1] = mp[pr.xr()];
		add(v, r, pr.xl(), tree[p].son[0]);
		add(v, r, pr.xr(), tree[p].son[1]);
	}
	if(r.yinsec(pr)){
		if(mp[pr.yl()] == mp.end()) mp[pr.yl()] = ++piv;
		if(mp[pr.yr()] == mp.end()) mp[pr.yr()] = ++piv;
		tree[p].son[2] = mp[pr.yl()];
		tree[p].son[3] = mp[pr.yr()];
		add(v, r, pr.yl(), tree[p].son[2]);
		add(v, r, pr.yr(), tree[p].son[3]);
	}
}

void init(int p = 0){
	if(tree[p].sons[0]){
		for(int j=0; j<2; j++){
			int des = tree[p].sons[j];
			tree[des].add += tree[p].add;
			init(des);
		}
		tree[p].add = 0;
		for(int j=0; j<2; j++){
			int des = tree[p].sons[j];
			tree[p].add = max(tree[p].add, tree[des].add);
			init(des);
		}
		return;
	}
	bool found = 0;

	for(int j=0; j<4; j++){
		if(tree[p].sons[j]){
			int des = tree[p].sons[j];
			tree[des].add += tree[p].add;
			found = 1;
		}
	}
	if(tree[p].sons){
		for(int j=tree[p].sons * 4 - 3; j < tree[p].sons * 4 + 1; j++){
			tree[j].add += tree[p].add;
		}
		tree[p].add = 0;
		for(int j=tree[p].sons * 4 - 3; j < tree[p].sons * 4 + 1; j++){
			init(j);
			tree[p].add = max(tree[p].add, tree[j].add);
		}
	}
}

lint query(rect r, rect pr = rect(1, n, 1, n), int p = 0){
	if(r.contain(pr)) return tree[p].add;
	lint ret = 0ll;
	if(tree[p].sons){
		if(r.insec(pr.ll())) ret = max(ret, query(r, pr.ll(), tree[p].sons * 4 - 3));
		if(r.insec(pr.lr())) ret = max(ret, query(r, pr.lr(), tree[p].sons * 4 - 2));
		if(r.insec(pr.rl())) ret = max(ret, query(r, pr.rl(), tree[p].sons * 4 - 1));
		if(r.insec(pr.rr())) ret = max(ret, query(r, pr.rr(), tree[p].sons * 4 - 0));
	}
	else ret = tree[p].add;
	return ret;
}

int main(){
	assert(sizeof(size_t) == 8);
	int q1, q2; scanf("%d %d %d",&n,&q1,&q2);
	for(int i=0; i<q1; i++){
		int w = 69696969;
		//rect r; scanf("%d %d %d %d %d",&r.sx,&r.sy,&r.ex,&r.ey,&w);
		rect r;
		r.sx = rand() % n + 1;
		r.ex = rand() % n + 1;
		r.sy = rand() % n + 1;
		r.ey = rand() % n + 1;
		if(r.sx > r.ex) swap(r.sx, r.ex);
		if(r.sy > r.ey) swap(r.sy, r.ey);
		add(w, r);
		vis.clear();
	}
	cout << piv << endl;
	init();
	for(int i=0; i<q2; i++){
		rect r; scanf("%d %d %d %d",&r.sx,&r.sy,&r.ex,&r.ey);
		printf("%lld\n", query(r));
	}
}

