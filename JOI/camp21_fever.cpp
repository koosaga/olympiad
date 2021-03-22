#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 100005;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int n;
pi a[MAXN];
bool vis[MAXN];

auto get_dist = [](int x, int y){
	return abs(a[x].first - a[y].first) + abs(a[x].second - a[y].second);
};

auto get_move = [](int x, int dx, int dy, int v){
	return pi(a[x].first + dx * v, a[x].second + dy * v);
};

struct point{
	int x, y;
	lint d;
};

// bcc

struct fen{
	int tree[MAXN];
	void clear(){ memset(tree, 0, sizeof(tree)); }
	void add(int x, int v){
		for(int i = x + 1; i < MAXN; i += i & -i) tree[i] += v;
	}
	int query(int x){
		int ret = 0;
		for(int i = x + 1; i; i -= i & -i) ret += tree[i];
		return ret;
	}
	int kth(int x){
		int pos = 0;
		for(int i = 16; i >= 0; i--){
			if(pos + (1<<i) < MAXN && tree[pos + (1<<i)] < x){
				pos += (1<<i);
				x -= tree[pos];
			}
		}
		return pos;
	}
}bit[4];

vector<pair<pi, int>> v[4];

int find_prev(int x, pi p){
	int q = lower_bound(all(v[x]), make_pair(p, int(1e9))) - v[x].begin() - 1;
	int cnt = bit[x].query(q);
	if(cnt > 0) return v[x][bit[x].kth(cnt)].second;
	return -1;
}

int find_next(int x, pi p){
	int q = lower_bound(all(v[x]), make_pair(p, int(-1e9))) - v[x].begin() - 1;
	int cnt = bit[x].query(q);
	int pos = bit[x].kth(cnt + 1);
	if(pos == MAXN - 1) return -1;
	return v[x][pos].second;
}

void Erase(int i){
	vis[i] = 1;
	int x = a[i].first;
	int y = a[i].second;
	vector<pi> w = {
		pi(x, y), pi(y, x), pi(x+y, x-y), pi(x-y, x+y) };
	for(int i = 0; i < 4; i++){
		int pos = lower_bound(all(v[i]), make_pair(w[i], -1)) - v[i].begin();
		bit[i].add(pos, -1);
	}
}

bool reason[MAXN][4][4];

struct gun{
	int pos;
	int md, yd;
	lint d;
	int idx;
	gun forward(){
		int x = a[pos].first;
		int y = a[pos].second;
		int cdx = dx[md] - dx[yd];
		int cdy = dy[md] - dy[yd];
		if(abs(cdx) == 2) cdx /= 2;
		if(abs(cdy) == 2) cdy /= 2;
		int val = (cdx + 1) * 3 + (cdy + 1);
		int i = -1;
		switch (val) {
			case 0: { 
				pi p(x - y, x + y - 2 * d);
				i = find_prev(3, p);
				break;
			}
			case 1: { 
				pi p(y, x - 2 * d);
				i = find_prev(1, p);
				break;
			}
			case 2: {
				pi p(x + y, x - y - 2 * d);
				i = find_prev(2, p);
				break;
			}
			case 3: {
				pi p(x, y - 2 * d);
				i = find_prev(0, p);
				break;
			}
			case 5: {
				pi p(x, y + 2 * d);
				i = find_next(0, p);
				break;
			}
			case 6: {
				pi p(x + y, x - y + 2 * d);
				i = find_next(2, p);
				break;
			}
			case 7: {
				pi p(y, x + 2 * d);
				i = find_next(1, p);
				break;
			}
			case 8: {
				pi p(x - y, x + y + 2 * d);
				i = find_next(3, p);
				break;
			}
			default: {
				assert(0);
				break;
			}
		}
		gun ng = *this;
		ng.d = 1e18;
		if(i == -1){
			return ng;
		}
		assert(!vis[i]);
	//	cout << i << " " << md << " " << yd << " " << cdx << " " << cdy << " " <<  endl;
		lint curd = get_dist(pos, i);
		if(curd / 2 < d || get_move(pos, dx[md], dy[md], curd / 2) != get_move(i, dx[yd], dy[yd], curd / 2)) return ng;
		ng.d = curd / 2;
		ng.idx = i;
		return ng;
	}
	bool operator<(const gun &g)const{
		return d > g.d;
	}
};

int main(){
	scanf("%d",&n);
	for(int i = 0; i < n; i++){
		scanf("%lld %lld",&a[i].first,&a[i].second);
		a[i].first *= 2;
		a[i].second *= 2;
	}
	pi zp = a[0];
	sort(a, a + n);
	int st = lower_bound(a, a + n, zp) - a;
	int dap = 0;
	for(int i = 0; i < n; i++){
		int x = a[i].first;
		int y = a[i].second;
		v[0].emplace_back(pi(x, y), i);
		v[1].emplace_back(pi(y, x), i);
		v[2].emplace_back(pi(x+y, x-y), i);
		v[3].emplace_back(pi(x-y, x+y), i);
	}
	for(int j = 0; j < 4; j++) sort(all(v[j]));
	for(int d = 0; d < 4; d++){
		memset(reason, 0, sizeof(reason));
		memset(vis, 0, sizeof(vis));
		for(int j = 0; j < 4; j++){
			bit[j].clear();
			for(int k = 0; k < n; k++) bit[j].add(k, 1);
		}
		priority_queue<gun> pq;
		auto enqueue = [&](int x, int y, lint d){
			if(vis[x]) return;
			Erase(x);
			point p = (point){x, y, d};
			for(int i = 0; i < 4; i++){
				if(p.y != i){
					gun g = {p.x, p.y, i, p.d};
					g = g.forward();
					if(g.d < 1e17) pq.push(g);
				}
			}
		};
		enqueue(st, d, 0);
		while(sz(pq)){
			auto x = pq.top(); pq.pop();
			if(vis[x.idx]){
				if(reason[x.idx][x.md][x.yd]) continue;
			}
			reason[x.idx][x.md][x.yd] = 1;
			enqueue(x.idx, x.yd, x.d);
			x.d++;
			x = x.forward();
			if(x.d < 1e17) pq.push(x);
		}
		dap = max(dap, (int)count(vis, vis + n, 1));
	}
	cout << dap << endl;
}

