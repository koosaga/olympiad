#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;
const lint INFTY = 1e10;

struct bit{
	int tree[MAXN];
	void clear(){
		memset(tree, 0, sizeof(tree));
	}
	void add(int x, int v){
		while(x < MAXN){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		for(int i=x; i; i-=i&-i) ret += tree[i];
		return ret;
	}
}bit;

struct sweeper{
	lint sx, ex, sy, ey;
	int idx;
	sweeper(lint sx, lint ex, lint sy, lint ey, int idx): sx(sx), ex(ex), sy(sy), ey(ey), idx(idx) {}
};

struct event{
	lint pos, x, y;
	int idx, buho;
	bool operator<(const event &e)const{
		return pos < e.pos;
	}
};

int n, q, ret[MAXN * 2];
pi a[MAXN], x[MAXN], y[MAXN];

void do_sweep(vector<sweeper> sweeps){
	vector<lint> v = {-lint(1e18)};
	vector<event> evt;
	for(int i=0; i<n; i++) v.push_back(a[i].second);
	sort(all(v)); v.resize(unique(all(v)) - v.begin());
	for(auto &i : sweeps){
		evt.push_back({i.ex, i.sy, i.ey, i.idx, +1});
		evt.push_back({i.sx-1, i.sy, i.ey, i.idx, -1});
	}
	sort(all(evt));
	int j = 0;
	bit.clear();
	for(auto &i : evt){
		while(j < n && a[j].first <= i.pos){
			int k = lower_bound(all(v), a[j].second) - v.begin();
			bit.add(k, 1);
			j++;
		}
		int l = lower_bound(all(v), i.x) - v.begin();
		int r = upper_bound(all(v), i.y) - v.begin();
		ret[i.idx] += i.buho * (bit.query(r - 1) - bit.query(l - 1));
	}
}

int main(){
	scanf("%*d %*d %d %d",&n,&q);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
	}
	for(int i=0; i<q; i++){
		scanf("%d %d",&x[i].first,&x[i].second);
		scanf("%d %d",&y[i].first,&y[i].second);
	}
	auto DIV = [&](lint x){
		if(x & 1) return (x - 1) / 2;
		return x / 2;
	};
	for(int i=0; i<4; i++){
		for(int j=0; j<n; j++){
			a[j] = pi(-a[j].second, a[j].first);
		}
		sort(a, a + n);
		for(int j=0; j<q; j++){
			x[j] = pi(-x[j].second, x[j].first);
			y[j] = pi(-y[j].second, y[j].first);
		}
		vector<sweeper> Ysweep, YPXsweep, YMXsweep;
		for(int j=0; j<q; j++){
			if(x[j].second >= y[j].second) continue;
			lint up = 1ll * x[j].second + 1ll * y[j].second + abs(x[j].first - y[j].first);
			lint dn = 1ll * x[j].second + 1ll * y[j].second - abs(x[j].first - y[j].first);
			if(y[j].second - x[j].second > abs(x[j].first - y[j].first)){	
				if(x[j].first < y[j].first){
					Ysweep.emplace_back(-INFTY, x[j].first, -INFTY, DIV(up - 1), 2 * j);
					YPXsweep.emplace_back(x[j].first + 1, y[j].first, -INFTY, DIV(up + 2 * x[j].first - 1), 2 * j);
					Ysweep.emplace_back(y[j].first + 1, INFTY, -INFTY, DIV(dn - 1), 2 * j);

					Ysweep.emplace_back(-INFTY, x[j].first, DIV(up) + 1, INFTY, 2 * j + 1);
					YPXsweep.emplace_back(x[j].first + 1, y[j].first, DIV(up + 2 * x[j].first) + 1, INFTY, 2 * j + 1);
					Ysweep.emplace_back(y[j].first + 1, INFTY, DIV(dn) + 1, INFTY, 2 * j + 1);
				}
				else{

					Ysweep.emplace_back(-INFTY, y[j].first, -INFTY, DIV(dn - 1), 2 * j);
					YMXsweep.emplace_back(y[j].first + 1, x[j].first, -INFTY, DIV(up - 2 * x[j].first - 1), 2 * j);
					Ysweep.emplace_back(x[j].first + 1, INFTY, -INFTY, DIV(up - 1), 2 * j);

					Ysweep.emplace_back(-INFTY, y[j].first, DIV(dn) + 1, INFTY, 2 * j + 1);
					YMXsweep.emplace_back(y[j].first + 1, x[j].first, DIV(up - 2 * x[j].first) + 1, INFTY, 2 * j + 1);
					Ysweep.emplace_back(x[j].first + 1, INFTY, DIV(up) + 1, INFTY, 2 * j + 1);
				}
			}
			if(y[j].first - x[j].first == y[j].second - x[j].second){
				Ysweep.emplace_back(-INFTY, x[j].first - 1, -INFTY, DIV(up - 1), 2 * j);
				YPXsweep.emplace_back(x[j].first, y[j].first - 1, -INFTY, DIV(up + 2 * x[j].first - 1), 2 * j);

				YPXsweep.emplace_back(x[j].first + 1, y[j].first, DIV(up + 2 * x[j].first) + 1, INFTY, 2 * j + 1);
				Ysweep.emplace_back(y[j].first + 1, INFTY, DIV(dn) + 1, INFTY, 2 * j + 1);
			}
		}
		do_sweep(Ysweep);
		for(int j=0; j<n; j++) a[j].second += a[j].first;
		do_sweep(YPXsweep);
		for(int j=0; j<n; j++) a[j].second -= 2 * a[j].first;
		do_sweep(YMXsweep);
		for(int j=0; j<n; j++) a[j].second += a[j].first;
	}
	for(int i=0; i<q; i++){
		printf("%d %d %d\n", ret[2*i], ret[2*i+1], n - ret[2*i] - ret[2*i+1]);
	}
}

