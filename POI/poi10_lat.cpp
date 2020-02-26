#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXT = 4200000;

struct event{
	int pos, sx, ex, delta;
	bool operator<(const event &e)const{
		return pi(pos, delta) < pi(e.pos, e.delta);
	}
};

struct query{
	int sx, ex, sy, ey, idx;
	bool operator<(const query &q)const{
		return ex < q.ex;
	}
};

int thres;

struct seg{
	struct node{
		int maxv, lazy, upd, updmax;
	}tree[MAXT];
	void init(int n){
		int lim;
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 2*lim, (node){0, 0, 0, 0});
	}
	void lazydown(int p){
		for(int i=2*p; i<2*p+2; i++){
			tree[i].maxv += tree[p].lazy;
			tree[i].lazy += tree[p].lazy;
			if(tree[i].maxv == tree[p].maxv){
				tree[i].upd = max(tree[i].upd, tree[p].upd);
				tree[i].updmax = max(tree[i].updmax, tree[p].upd);
			}
		}
		tree[p].upd = 0;
		tree[p].lazy = 0;
	}
	void upd(int s, int e, int ps, int pe, int p, int v, int t){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			bool upd = (tree[p].maxv == thres);
			tree[p].maxv += v;
			tree[p].lazy += v;
			upd &= (tree[p].maxv != thres);
			if(upd){
				tree[p].upd = t - 1;
				tree[p].updmax = t - 1;
			}
			return;
		}
		lazydown(p);
		int pm = (ps+pe)/2;
		upd(s, e, ps, pm, 2*p, v, t);
		upd(s, e, pm+1, pe, 2*p+1, v, t);
		tree[p].maxv = max(tree[2*p].maxv, tree[2*p+1].maxv);
		tree[p].updmax = max(tree[2*p].updmax, tree[2*p+1].updmax);
	}
	int query1(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return 0;
		if(s <= ps && pe <= e) return tree[p].maxv;
		lazydown(p);
		int pm = (ps+pe)/2;
		return max(query1(s, e, ps, pm, 2*p), query1(s, e, pm+1, pe, 2*p+1));
	}
	int query2(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return 0;
		if(s <= ps && pe <= e) return tree[p].updmax;
		lazydown(p);
		int pm = (ps+pe)/2;
		return max(query2(s, e, ps, pm, 2*p), query2(s, e, pm+1, pe, 2*p+1));
	}
}seg;

bool chk[666];

void solve(vector<event> upds, vector<query> ques, int n, int m, int _thres){
	thres = _thres;
	int p1 = 0, p2 = 0;
	seg.init(m);
	sort(all(upds));
	sort(all(ques));
	for(int i=0; i<n; i++){
		while(p2 < sz(ques) && ques[p2].ex == i){
			int s = ques[p2].sy;
			int e = ques[p2].ey;
			if(chk[ques[p2].idx]){
				p2++;
				continue;
			}
			if(seg.query1(s, e - 1, 0, m - 1, 1) == thres){
				chk[ques[p2].idx] = 1;
			}
			else if(seg.query2(s, e - 1, 0, m - 1, 1) > ques[p2].sx){
				chk[ques[p2].idx] = 1;
			}
			p2++;
		}
		while(p1 < sz(upds) && upds[p1].pos == i){
			seg.upd(upds[p1].sx, upds[p1].ex - 1, 0, m - 1, 1, upds[p1].delta, i+1);
			p1++;
		}
	}
}

struct frac{
	int x, y;
	frac(){}
	frac(int x, int y): x(x), y(y) {}
	bool operator<(const frac &f)const{
		return 1ll * x * f.y < 1ll * y * f.x;
	}
	bool operator==(const frac &f)const{
		return 1ll * x * f.y == 1ll * y * f.x;
	}
};

struct rect{
	frac sx, ex, sy, ey;
	rect(){}
	rect(frac sx, frac ex, frac sy, frac ey) : sx(sx), ex(ex), sy(sy), ey(ey) {}
};

int main(){
	int n, m;
	cin >> n >> m;
	vector<int> sx(n+m), ex(n+m), sy(n+m), ey(n+m);
	for(int i=0; i<n+m; i++){
		cin >> sx[i] >> sy[i] >> ex[i] >> ey[i];
	}
	for(int i=2; i<=1024; i<<=1){
		vector<rect> stab;
		vector<rect> quer;
		for(int j=1; j<=i; j++){
			if(j % 2 == 0){
				for(int x=0; x<n; x++){
					if(j < i) stab.emplace_back(frac(sx[x], j), frac(ex[x], j), frac(sy[x], j), frac(ey[x], j));
					else quer.emplace_back(frac(sx[x], j), frac(ex[x], j), frac(sy[x], j), frac(ey[x], j));
				}
			}
			else{
				for(int x=n; x<n+m; x++){
					stab.emplace_back(frac(sx[x], j), frac(ex[x], j), frac(sy[x], j), frac(ey[x], j));
				}
			}
		}
		vector<frac> vx, vy;
		for(auto &i : stab){
			vx.push_back(i.sx);
			vx.push_back(i.ex);
			vy.push_back(i.sy);
			vy.push_back(i.ey);
		}
		for(auto &i : quer){
			vx.push_back(i.sx);
			vx.push_back(i.ex);
			vy.push_back(i.sy);
			vy.push_back(i.ey);
		}
		sort(all(vx));
		vx.resize(unique(all(vx)) - vx.begin());
		sort(all(vy));
		vy.resize(unique(all(vy)) - vy.begin());
		vector<event> upds;
		vector<query> ques;
		int idx = 0;
		for(auto &i : stab){
			int isx = lower_bound(all(vx), i.sx) - vx.begin();
			int isy = lower_bound(all(vy), i.sy) - vy.begin();
			int iex = lower_bound(all(vx), i.ex) - vx.begin();
			int iey = lower_bound(all(vy), i.ey) - vy.begin();
			upds.push_back({isx, isy, iey, +1});
			upds.push_back({iex, isy, iey, -1});
		}
		for(auto &i : quer){
			int isx = lower_bound(all(vx), i.sx) - vx.begin();
			int isy = lower_bound(all(vy), i.sy) - vy.begin();
			int iex = lower_bound(all(vx), i.ex) - vx.begin();
			int iey = lower_bound(all(vy), i.ey) - vy.begin();
			ques.push_back({isx, iex, isy, iey, idx});
			idx++;
		}
		solve(upds, ques, sz(vx), sz(vy), i - 1);
	}
	cout << count(chk, chk + 666, 1) << endl;
	for(int i=0; i<n; i++){
		if(chk[i]) printf("%d ", i + 1);
	}
	puts("");
}
