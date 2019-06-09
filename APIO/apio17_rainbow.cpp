#include "rainbow.h"
#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXT = 20000000;
const int MAXN = 200005;

struct node{
	int l, r, sum;
}pool[MAXT];
int piv;

int newnode(){ return ++piv; }

void init(int s, int e, int p){
	if(s == e) return;
	int m = (s+e)/2;
	pool[p].l = newnode();
	pool[p].r = newnode();
	init(s, m, pool[p].l);
	init(m+1, e, pool[p].r);
}

void add(int pos, int s, int e, int prv, int cur){
	pool[cur].sum = pool[prv].sum + 1;
	if(s == e) return;
	int m = (s+e)/2;
	if(pos <= m){
		pool[cur].l = newnode();
		pool[cur].r = pool[prv].r;
		add(pos, s, m, pool[prv].l, pool[cur].l);
	}
	else{
		pool[cur].l = pool[prv].l;
		pool[cur].r = newnode();
		add(pos, m+1, e, pool[prv].r, pool[cur].r);
	}
}

int query(int s, int e, int ps, int pe, int p){
	if(e < ps || pe < s) return 0;
	if(s <= ps && pe <= e) return pool[p].sum;
	int pm = (ps + pe) / 2;
	return query(s, e, ps, pm, pool[p].l) + query(s, e, pm+1, pe, pool[p].r);
}

int tree[4][MAXN];
vector<int> v[4][MAXN];
int minx = 1e9, miny = 1e9, maxx = -1e9, maxy = -1e9, yMax;

void init(int R, int C, int sr, int sc, int M, char *S) {
	auto upload = [&](int x, int y){
		v[0][x].push_back(y);
		v[0][x].push_back(y + 1);
		v[0][x + 1].push_back(y);
		v[0][x + 1].push_back(y + 1);
		v[1][x].push_back(y);
		v[1][x].push_back(y + 1);
		v[2][x].push_back(y);
		v[2][x + 1].push_back(y);
		v[3][x].push_back(y);
		minx = min(minx, x); maxx = max(maxx, x + 1);
		miny = min(miny, y); maxy = max(maxy, y + 1);
	};
	upload(sr, sc);
	for(int i=0; i<M; i++){
		if(S[i] == 'N') sr--;
		if(S[i] == 'S') sr++;
		if(S[i] == 'E') sc++;
		if(S[i] == 'W') sc--;
		upload(sr, sc);
	}
	yMax = C + 1;
	for(int i=0; i<4; i++){
		tree[i][0] = newnode();
		init(1, yMax, tree[i][0]); 
		for(int j=1; j<=R+1; j++){
			sort(v[i][j].begin(), v[i][j].end());
			v[i][j].resize(unique(v[i][j].begin(), v[i][j].end()) - v[i][j].begin());
			int prv = tree[i][j-1];
			for(auto &k : v[i][j]){
				int nxt = newnode();
				add(k, 1, yMax, prv, nxt);
				prv = nxt;
			}
			tree[i][j] = prv;
		}
	}
}

int colour(int ar, int ac, int br, int bc) {
	auto query_helper = [&](int idx, int sx, int ex, int sy, int ey){
		return query(sy, ey, 1, yMax, tree[idx][ex]) 
		- query(sy, ey, 1, yMax, tree[idx][sx - 1]);
	};
	int V = query_helper(0, ar + 1, br, ac + 1, bc);
	int E = query_helper(1, ar, br, ac + 1, bc) + query_helper(2, ar + 1, br, ac, bc);
	int F = query_helper(3, ar, br, ac, bc);
	if(ar < minx && maxx < br + 1 && ac < miny && maxy < bc + 1){
		return 2 + E - V - F;
	}
	return 1 + E - V - F;
}

