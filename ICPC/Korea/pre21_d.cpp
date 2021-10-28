#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
using point = complex<llf>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 2005;
const int mod = 1e9 + 7;

int n, m;

struct intv{
	int s, e, x;
	bool operator<(const intv &i)const{
		return s < i.s;
	}
}v[MAXN];

int dp[MAXN][MAXN];

int main(){
	vector<int> vtx;
	scanf("%d %d",&n,&m);
	vector<int> a(n);
	for(auto &i : a) scanf("%d",&i);
	sort(all(a));
	vtx.push_back(0);
	vtx.push_back(n);
	for(int i = 0; i < m; i++){
		int l, r, x;
		scanf("%d %d %d",&l,&r,&x);
		l = lower_bound(all(a), l) - a.begin();
		r = lower_bound(all(a), r) - a.begin();
		v[i] = {l, r, x};
		vtx.push_back(l);
		vtx.push_back(r);
	}
	sort(v, v + m);
	sort(all(vtx));
	vtx.resize(unique(all(vtx)) - vtx.begin());
	for(int i = 0; i < m; i++){
		v[i].s = lower_bound(all(vtx), v[i].s) - vtx.begin();
		v[i].e = lower_bound(all(vtx), v[i].e) - vtx.begin();
	}
	n = sz(vtx) - 1;
	int ret = 2.1e9;
	for(int j = m - 1; j >= 0; j--){
		vector<int> pfx(n + 1, 2.1e9);
		for(int k = j + 1; k < m; k++){
			if(v[k].s > v[j].e) continue;
			pfx[v[k].s] = min(pfx[v[k].s], dp[j][k]);
		}
		for(int k = n - 1; k >= 0; k--) pfx[k] = min(pfx[k], pfx[k + 1]);
		for(int i = j-1; i >= 0; i--){
			dp[i][j] = 2.1e9;
			if(v[i].e < v[j].s || v[i].e >= v[j].e) continue;
			if(v[j].e == n){
				dp[i][j] = max(v[i].x, v[j].x);
				if(v[j].s < v[i].e) dp[i][j] = v[i].x + v[j].x;
			}
			dp[i][j] = min(dp[i][j], pfx[v[i].e]);
			dp[i][j] = max(dp[i][j], v[i].x);
			dp[i][j] = max(dp[i][j], v[j].x);
			if(v[j].s < v[i].e) dp[i][j] = max(dp[i][j], v[i].x + v[j].x);
			if(v[i].s == 0) ret = min(ret, dp[i][j]);
		}
		if(v[j].s == 0 && v[j].e == n) ret = min(ret, v[j].x);
	}
	if(ret > 2.01e9) ret = -1;
	cout << ret << endl;
}
