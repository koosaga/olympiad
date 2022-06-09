#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const int MAXN = 100005;
const int MAXT = 530000;

pi operator+(pi a, pi b){
		pi ret;
		ret.first = max(a.first, b.first);
		ret.second = (a.first == ret.first ? a.second : 0) + (b.first == ret.first ? b.second : 0);
		return ret;
}
struct seg{
	pi tree[MAXT];
	int lazy[MAXT];
	void init(int s, int e, int p){
		tree[p] = pi(0, e-s+1);
		lazy[p] = 0;
		if(s == e){
			return;
		}
		int m = (s+e)/2;
		init(s, m, 2*p);
		init(m+1, e, 2*p+1);
	}
	void lazydown(int p){
		for(int i = 2*p; i < 2*p+2; i++){
			lazy[i] += lazy[p];
			tree[i].first += lazy[p];
		}
		lazy[p] = 0;
	}
	void add(int s, int e, int ps, int pe, int p, int v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p].first += v;
			lazy[p] += v;
			return;
		}
		int pm = (ps+pe)/2;
		lazydown(p);
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = tree[2*p] + tree[2*p+1];
	}
	pi query(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return pi(0, 0);
		if(s <= ps && pe <= e) return tree[p];
		lazydown(p);
		int pm = (ps+pe)/2;
		return query(s, e, ps, pm, 2*p) + query(s, e, pm+1, pe, 2*p+1);
	}
}seg;

struct event{
	int s, e, x;
};

void solve(){
	int n, c; cin >> n >> c;
	vector<pi> intv(c);
	for(int i = 0; i < c; i++){
		cin >> intv[i].first >> intv[i].second;
	}
	vector<int> a(n), cnt(c);
	for(auto &i : a){
		cin >> i;
		i--;
		cnt[i]++;
	}
	for(int i = 0; i < c; i++){
		intv[i].second = min(intv[i].second, cnt[i]);
		intv[i].first = max(intv[i].first, 1);
	}
	vector<event> sweeps[2 * MAXN];
	auto addVal = [&](int sx, int ex, int sy, int ey){
		if(sx > ex || sy > ey) return;
	//	cout << sx << " " << ex << " " << sy << " " << ey << endl;
		sweeps[sx].push_back({sy, ey, +1});
		sweeps[ex + 1].push_back({sy, ey, -1});
	};
	{
		vector<vector<int>> palette(c);
		for(int i = 0; i < n; i++){
			palette[a[i]].push_back(i);
			palette[a[i]].push_back(i + n);
		}
		for(int i = 0; i < c; i++){
			palette[i].push_back(-1);
			palette[i].push_back(2 * n);
			sort(all(palette[i]));
			for(int j = 1; j < sz(palette[i]); j++){
				int l = palette[i][j - 1] + 1;
				int r = palette[i][j] - 1;
				addVal(l, r, l, r);
				if(intv[i].first <= intv[i].second){
					int sl = (j + intv[i].first - 1 < sz(palette[i]) ? palette[i][j + intv[i].first - 1] : 1e9);
					int sr = (j + intv[i].second < sz(palette[i]) ? palette[i][j + intv[i].second] : 1e9) - 1;
					sr = min(sr, 2 * n - 1);
					addVal(l, r + 1, sl, sr);
				}
			}
		}
	}
	seg.init(0, 2 * n - 1, 1);
	lint ret = 0;
	for(int i = 0; i < n; i++){
		for(auto &j : sweeps[i]){
			seg.add(j.s, j.e, 0, 2 * n - 1, 1, j.x);
		}
		auto q = seg.query(i + 1, i + n - 2, 0, 2 * n - 1, 1);
		if(q.first == c) ret += q.second;
	}
	cout << ret << "\n";
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int tc; cin >> tc;
	for(int i = 1; i <= tc; i++){
		cout << "Case #" << i << ": ";
		solve();
	}
}
