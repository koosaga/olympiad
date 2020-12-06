#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1005;

int n, w, d, a[MAXN], b[MAXN], c[MAXN];
vector<int> v[MAXN];
vector<vector<pi>> gph[MAXN];

int dist(int x, int y){ return abs(a[x] - a[y]) + abs(b[x] - b[y]); }

void add_edge(int s, int e, int x, int y){
	int p1 = lower_bound(all(v[s]), x) - v[s].begin();
	int p2 = lower_bound(all(v[e]), x - y) - v[e].begin();
	gph[s][p1].emplace_back(e, p2);
}

vector<lint> dp[11][MAXN];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d %d",&a[i],&b[i],&c[i]);
	}
	scanf("%d %d",&w,&d);
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(i == j) continue;
			int dis = dist(i, j);
			if(dis <= w){
				v[i].push_back(w);
				v[j].push_back(w - dis);
				v[i].push_back(dis);
				v[j].push_back(0);
			}
		}
	}
	for(int i=0; i<n; i++){
		sort(all(v[i]));
		v[i].resize(unique(all(v[i])) - v[i].begin());
		gph[i].resize(sz(v[i]));
		for(int j=0; j<=10; j++){
			dp[j][i].resize(sz(v[i]));
			fill(all(dp[j][i]), 1e18);
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(i == j) continue;
			int dis = dist(i, j);
			if(dis <= w) add_edge(i, j, w, dis);
			if(dis < w) add_edge(i, j, dis, dis);
		}
	}
	dp[0][0][0] = 0;
	lint ret = 1e18;
	for(int i=0; i<d; i++){
		for(int j=0; j<n; j++){
			// prefixize
			for(int k = 1; k < sz(dp[i][j]); k++){
				dp[i][j][k] = min(dp[i][j][k], dp[i][j][k-1] + 1ll * c[j] * (v[j][k] - v[j][k-1]));
			}
			for(int k = 0; k < sz(dp[i][j]); k++){
				for(auto &[vtx, ptr] : gph[j][k]){
					dp[i + 1][vtx][ptr] = min(dp[i + 1][vtx][ptr], dp[i][j][k]);
				}
			}
		}
		for(auto &j : dp[i + 1][1]) ret = min(ret, j);
	}
	if(ret > 1e17) ret = -1;
	cout << ret << endl;
}
