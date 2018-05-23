#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 200005;
const int pool = 18000000;

vector<int> gph[pool];
struct node{ int l, r; }tree[pool];
int dis[pool], piv;
bool vis[pool];

void init(int s, int e, int p){
	if(s == e) return;
	tree[p].l = piv++;
	tree[p].r = piv++;
	int m = (s+e)/2;
	init(s, m, tree[p].l);
	init(m+1, e, tree[p].r);
}

void update(int pos, int s, int e, int prv, int cur, int v){
	if(s == e){
		if(v != -1) gph[cur].push_back(v);
		return;
	}
	int m = (s+e)/2;
	if(pos <= m){
		tree[cur].l = piv++;
		tree[cur].r = tree[prv].r;
		update(pos, s, m, tree[prv].l, tree[cur].l, v);
	}
	else{
		tree[cur].l = tree[prv].l;
		tree[cur].r = piv++;
		update(pos, m+1, e, tree[prv].r, tree[cur].r, v);
	}
}

void query(int s, int e, int ps, int pe, int p, int v, deque<int> &que){
	if(e < ps || pe < s) return;
	if(s <= ps && pe <= e){
		if(dis[p] > dis[v] + 1){
			dis[p] = dis[v] + 1;
			que.push_back(p);
		}
		return;
	}
	int pm = (ps+pe)/2;
	query(s, e, ps, pm, tree[p].l, v, que);
	query(s, e, pm+1, pe, tree[p].r, v, que);
}

int n, sx, sy;
pi s, e;
struct rect{ int sx, ex, sy, ey; }a[100005];
struct seg { int x, s, e, idx; }intv[400500];
vector<seg> segx, segy;

vector<pi> addE[MAXN];

vector<int> solve(vector<seg> &l){
	for(int i=0; i<MAXN; i++) addE[i].clear();
	for(auto &i : l){
		addE[i.s].push_back(pi(i.x, i.idx));
		addE[i.e+1].push_back(pi(i.x, -1));
	}
	int crt = piv++;
	init(0, MAXN - 1, crt);
	vector<int> ans;
	for(int i=0; i<MAXN; i++){
		for(auto &j : addE[i]){
			int nrt = piv++;
			update(j.first, 0, MAXN-1, crt, nrt, j.second);
			crt = nrt;
		}
		ans.push_back(crt);
	}
	return ans;
}

vector<pi> ins[MAXN], del[MAXN];

vector<seg> sweep(vector<pi> &v){
	for(int i=0; i<MAXN; i++) ins[i].clear(), del[i].clear();
	for(int i=0; i<n; i++){
		if(a[i].sx + 1 < a[i].ex){
			ins[a[i].sx + 1].push_back(pi(a[i].sy, a[i].ey));
			del[a[i].ex].push_back(pi(a[i].sy, a[i].ey));
		}
	}
	set<pi> intv;
	int ptr = 0;
	vector<seg> ret;
	for(int i=0; i<MAXN; i++){
		for(auto &j : ins[i]) intv.insert(j);
		for(auto &j : del[i]) intv.erase(j);
		while(ptr < v.size() && v[ptr].first == i){
			auto l = intv.lower_bound(pi(v[ptr].second, -1));
			int re = (l == intv.end() ? (2*n+2) : l->first);
			int rs = (l == intv.begin() ? 0 : prev(l)->second);
			ret.push_back({i, rs, re, piv++});
			ptr++;
		}
	}
	return ret;
}

bool chk[400505];

int main(){
	cin >> s.first >> s.second >> e.first >> e.second >> n;
	vector<int> vx = {s.first, e.first}, vy = {s.second, e.second};
	for(int i=0; i<n; i++){
		scanf("%d %d %d %d",&a[i].sx,&a[i].ex,&a[i].sy,&a[i].ey);
		vx.push_back(a[i].sx);
		vx.push_back(a[i].ex);
		vy.push_back(a[i].sy);
		vy.push_back(a[i].ey);
	}
	sort(vx.begin(), vx.end());
	vx.resize(unique(vx.begin(), vx.end()) - vx.begin());
	sort(vy.begin(), vy.end());
	vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
	auto getloc = [&](int x, vector<int> &v){
		return lower_bound(v.begin(), v.end(), x) - v.begin();
	};
	s.first = getloc(s.first, vx);
	s.second = getloc(s.second, vy);
	e.first = getloc(e.first, vx);
	e.second = getloc(e.second, vy);
	for(int i=0; i<n; i++){
		a[i].sx = getloc(a[i].sx, vx);
		a[i].ex = getloc(a[i].ex, vx);
		a[i].sy = getloc(a[i].sy, vy);
		a[i].ey = getloc(a[i].ey, vy);
	}
	sx = vx.size();
	sy = vy.size();
	vector<pi> ptr;
	ptr.push_back(s);
	ptr.push_back(e);
	for(int i=0; i<n; i++){
		ptr.emplace_back(a[i].sx, a[i].sy);
		ptr.emplace_back(a[i].ex, a[i].ey);
	}
	ptr.emplace_back(0, 0);
	ptr.emplace_back(sx-1, sy-1);
	sort(ptr.begin(), ptr.end());
	ptr.resize(unique(ptr.begin(), ptr.end()) - ptr.begin());
	segy = sweep(ptr);
	for(int i=0; i<n; i++){
		swap(a[i].sx, a[i].sy);
		swap(a[i].ex, a[i].ey);
	}
	for(auto &i : ptr) swap(i.first, i.second);
	sort(ptr.begin(), ptr.end());
	segx = sweep(ptr);
	sort(segx.begin(), segx.end(), [&](const seg &a, const seg &b){
		return a.x < b.x;
	});
	sort(segy.begin(), segy.end(), [&](const seg &a, const seg &b){
		return a.x < b.x;
	});
	auto xpers = solve(segy);
	auto ypers = solve(segx);
	deque<int> que;
	memset(dis, 0x3f, sizeof(dis));
	for(auto &i : segx){
		intv[i.idx] = i;
		if(i.x == s.second && i.s <= s.first && s.first <= i.e){
			dis[i.idx] = 0;
			que.push_back(i.idx);
		}
	}
	for(auto &i : segy){ // y parallel
		intv[i.idx] = i;
		chk[i.idx] = 1;
		if(i.x == s.first && i.s <= s.second && s.second <= i.e){
			dis[i.idx] = 0;
			que.push_back(i.idx);
		}
	}
	while(!que.empty()){
		int x = que.front();
		que.pop_front();
		if(vis[x]) continue;
		vis[x] = 1;
		if(tree[x].l && dis[tree[x].l] > dis[x]){
			dis[tree[x].l] = dis[x];
			que.push_front(tree[x].l);
		}
		if(tree[x].r && dis[tree[x].r] > dis[x]){
			dis[tree[x].r] = dis[x];
			que.push_front(tree[x].r);
		}
		for(auto &i : gph[x]){
			if(dis[i] > dis[x]){
				dis[i] = dis[x];
				que.push_front(i);
			}
		}
		if(x < segx.size() + segy.size()){
			if(chk[x]){
				int nd = ypers[intv[x].x];
				query(intv[x].s, intv[x].e, 0, MAXN-1, nd, x, que);
			}
			else{
				int nd = xpers[intv[x].x];
				query(intv[x].s, intv[x].e, 0, MAXN-1, nd, x, que);
			}
		}
	}
	int ret = 1e9;
	for(auto &i : segx){
		if(i.x == e.second && i.s <= e.first && e.first <= i.e){
			ret = min(ret, dis[i.idx]);
		}
	}
	for(auto &i : segy){
		if(i.x == e.first && i.s <= e.second && e.second <= i.e){
			ret = min(ret, dis[i.idx]);
		}
	}
	cout << ret + 1 << endl;
}


