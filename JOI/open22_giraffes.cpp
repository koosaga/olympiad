#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 8005;
const int mod = 1e9 + 7;

int a[MAXN];
int dp[2][MAXN][4];

struct rec{
	int sx, sy, ex, ey;
};

const int MAXT = 17000;

struct seg{
	int tree[MAXT], lim;
	void init(int n){
		memset(tree, 0x3f, sizeof(tree));
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void upd(int x, int v){
		x += lim;
		while(x){
			tree[x] = min(tree[x], v);
			x >>= 1;
		}
	}
	int query(int s, int e){
		s += lim;
		e += lim;
		int ret = 1e9;
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}seg;


int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int n; cin >> n;
	for(int i = 0; i < n; i++) cin >> a[i], a[i]--;
	for(int i = 0; i < n; i++){
		fill(dp[1][i], dp[1][i] + 4, 1);
	}
	int msk[4] = {3, 1, 0, 2};
	bool upd = 1;
	for(int i = 2; upd; i++){
		memset(dp[i%2], 0x3f, sizeof(dp[i%2]));
		upd = 0;
		vector<rec> rect;
		for(int j = 0; j < n; j++){
			for(int k = 0; k < 4; k++){
				if(dp[(i - 1) % 2][j][k] < 1e8){
					int d = dp[(i - 1) % 2][j][k];
					if(k == 0) rect.push_back({j, a[j], j + d, a[j] + d});
					if(k == 1) rect.push_back({j + 1 - d, a[j], j + 1, a[j] + d});
					if(k == 2) rect.push_back({j + 1 - d, a[j] + 1 - d, j + 1, a[j] + 1});
					if(k == 3) rect.push_back({j, a[j] + 1 - d, j  + d, a[j] + 1});
				}
			}
		}
		vector<rec> r(n);
		for(int i = 0; i < n; i++) r[i] = {i, a[i], i + 1, a[i] + 1};
		for(int p = 0; p < 4; p++){
			sort(all(rect), [&](const rec &a, const rec &b){
				return a.sy - a.sx < b.sy - b.sx;
			});
			vector<int> idx(n); iota(all(idx), 0);
			sort(all(idx), [&](const int &a, const int &b){
				return r[a].ey - r[a].ex < r[b].ey - r[b].ex;
			});
			{
				seg.init(n);
				int ptr = sz(rect);
				for(int jj = n - 1; jj >= 0; jj--){
					int j = idx[jj];
					while(ptr > 0 && r[j].ey - r[j].ex <= rect[ptr-1].sy - rect[ptr-1].sx){
						seg.upd(rect[ptr-1].sx, rect[ptr-1].ey);
						ptr--;
					}
					dp[i % 2][j][p] = min(dp[i % 2][j][p], seg.query(r[j].ex, n) - r[j].ey + 1);
				}
			}
			{
				seg.init(n);
				int ptr = 0;
				for(int jj = 0; jj < n; jj++){
					int j = idx[jj];
					while(ptr < sz(rect) && r[j].ey - r[j].ex >= rect[ptr].sy - rect[ptr].sx){
						seg.upd(rect[ptr].sy, rect[ptr].ex);
						ptr++;
					}
					dp[i % 2][j][p] = min(dp[i % 2][j][p], seg.query(r[j].ey, n) - r[j].ex + 1);
				}
			}
			for(auto &k : rect){
				tie(k.sx, k.sy) = pi(k.sy, n - k.sx);
				tie(k.ex, k.ey) = pi(k.ey, n - k.ex);
				if(k.sx > k.ex) swap(k.sx, k.ex);
				if(k.sy > k.ey) swap(k.sy, k.ey);
			}
			for(auto &k : r){
				tie(k.sx, k.sy) = pi(k.sy, n - k.sx);
				tie(k.ex, k.ey) = pi(k.ey, n - k.ex);
				if(k.sx > k.ex) swap(k.sx, k.ex);
				if(k.sy > k.ey) swap(k.sy, k.ey);
			}
		}
		for(int j = 0; j < n; j++){
			if(j + dp[i%2][j][0] <= n && a[j] + dp[i % 2][j][0] <= n) upd = 1;
			else dp[i % 2][j][0] = 1e9;
			if(j + 1 - dp[i%2][j][1] >= 0 && a[j] + dp[i % 2][j][1] <= n) upd = 1;
			else dp[i % 2][j][1] = 1e9;
			if(j + 1 - dp[i%2][j][2] >= 0 && a[j] + 1 - dp[i % 2][j][2] >= 0) upd = 1;
			else dp[i % 2][j][2] = 1e9;
			if(j + dp[i%2][j][3] <= n && a[j] + 1 - dp[i % 2][j][3] >= 0) upd = 1;
			else dp[i % 2][j][3] = 1e9;
		}
		if(!upd){
			cout << n - (i - 1) << "\n";
			return 0;
		}
	}
}
