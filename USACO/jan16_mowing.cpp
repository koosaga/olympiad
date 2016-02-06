#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

struct edg{
	int s, e, x, y;
	bool operator<(const edg &b)const{
		return x < b.x;
	}
};

struct sweep{
	int pos, x, y;
	bool operator<(const sweep &b)const{
		return pos < b.pos;
	}
};

int n, t;
vector<edg> vx, vy;
vector<sweep> ins, del;

struct nodey{
	nodey *ls, *rs;
	int sum;
	nodey(){
		ls = rs = NULL;
		sum = 0;
	}
};

struct nodex{
	nodex *ls, *rs;
	nodey *ys;
	nodex(){
		ls = rs = NULL;
		ys = NULL;
	}
}*root;

void addy(int pos, int s, int e, int v, nodey *p){
	p->sum+=v;
	if(s == e) return;
	int m = (s+e)/2;
	if(pos <= m){
		if(!p->ls) p->ls = new nodey();
		addy(pos, s, m, v, p->ls);
	}
	else{
		if(!p->rs) p->rs = new nodey();
		addy(pos, m+1, e, v, p->rs);
	}
}

void addx(int px, int py, int s, int e, int v, nodex *p){
	if(!p->ys) p->ys = new nodey();
	addy(py, 1, n, v, p->ys);
	if(s == e) return;
	int m = (s+e)/2;
	if(px <= m){
		if(!p->ls) p->ls = new nodex();
		addx(px, py, s, m, v, p->ls);
	}
	else{
		if(!p->rs) p->rs = new nodex();
		addx(px, py, m+1, e, v, p->rs);
	}
}

int queryy(int s, int e, int ps, int pe, nodey *p){
	if(p == NULL) return 0;
	if(e < ps || pe < s) return 0;
	if(s <= ps && pe <= e) return p->sum;
	int pm = (ps + pe) / 2;
	return queryy(s, e, ps, pm, p->ls) + queryy(s, e, pm+1, pe, p->rs);
}

int queryx(int s, int e, int sy, int ey, int ps, int pe, nodex *p){
	if(p == NULL) return 0;
	if(e < ps || pe < s) return 0;
	if(s <= ps && pe <= e) return queryy(sy, ey, 1, n, p->ys);
	int pm = (ps + pe) / 2;
	return queryx(s, e, sy, ey, ps, pm, p->ls) + queryx(s, e, sy, ey, pm+1, pe, p->rs);
}

multiset<pi> swpline;

void solve(){
	root = new nodex();
	lint ret = 0;
	int ps = 0, py = 0, pd = 0;
	for(int i=1; i<=n; i++){
		while(ps < ins.size() && ins[ps].pos == i){
			addx(ins[ps].x, ins[ps].y, 1, n, 1, root);
			ps++;
		}
		while(py < vy.size() && vy[py].x == i){
			int s = vy[py].s, e = vy[py].e, y = vy[py].y;
			ret += queryx(s, e, 1, max(0, y - t), 1, n, root);
			ret += queryx(s, e, min(y+t, n+1), n, 1, n, root);
			py++;
		}
		while(pd < del.size() && del[pd].pos == i){
			addx(del[pd].x, del[pd].y, 1, n, -1, root);
			pd++;
		}
	}
	printf("%lld",ret);
}

int main(){
	freopen("mowing.in","r",stdin);
	freopen("mowing.out","w",stdout);
	scanf("%d %d",&n,&t);
	vector<int> px, py;
	px.push_back(-1);
	py.push_back(-1);
	int x, y;
	scanf("%d %d",&x,&y);
	px.push_back(x);
	py.push_back(y);
	for(int i=1; i<n; i++){
		int cx, cy;
		scanf("%d %d",&cx,&cy);
		if(cx == x){
			vx.push_back({min(y, cy), max(y, cy), x, i});
		}
		else{
			vy.push_back({min(x, cx), max(x, cx), y, i});
		}
		px.push_back(cx);
		py.push_back(cy);
		x = cx, y = cy;
	}
	sort(px.begin(), px.end());
	px.resize(unique(px.begin(), px.end()) - px.begin());
	sort(py.begin(), py.end());
	py.resize(unique(py.begin(), py.end()) - py.begin());
	for(auto &i : vx){
		i.s = lower_bound(py.begin(), py.end(), i.s) - py.begin() + 1;
		i.e = lower_bound(py.begin(), py.end(), i.e) - py.begin() - 1;
		i.x = lower_bound(px.begin(), px.end(), i.x) - px.begin();
		if(i.s > i.e) continue;
		ins.push_back({i.s, i.x, i.y});
		del.push_back({i.e, i.x, i.y});
	}
	sort(ins.begin(), ins.end());
	sort(del.begin(), del.end());
	for(auto &i : vy){
		i.s = lower_bound(px.begin(), px.end(), i.s) - px.begin() + 1;
		i.e = lower_bound(px.begin(), px.end(), i.e) - px.begin() - 1; 
		i.x = lower_bound(py.begin(), py.end(), i.x) - py.begin();
	}
	sort(vy.begin(), vy.end());
	solve();
}