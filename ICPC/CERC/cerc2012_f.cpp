#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
const int MAXN = 100005;
const int mod = 1e9 + 7;
using lint = long long;
using pi = pair<lint, lint>;

int n, m;
lint dist[2][MAXN];
vector<pi> gph[MAXN];

void solve(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++) gph[i].clear();
	for(int i=0; i<m; i++){
		int s, e, x; scanf("%d %d %d",&s,&e,&x);
		s--, e--;
		gph[s].emplace_back(x, e);
		gph[e].emplace_back(x, s);
	}
	memset(dist, 0x3f, sizeof(dist));
	for(int i=0; i<2; i++){
		dist[i][i] = 0;
		priority_queue<pi, vector<pi>, greater<pi> > pq;
		pq.emplace(0, i);
		while(!pq.empty()){
			auto x = pq.top(); pq.pop();
			if(dist[i][x.second] != x.first) continue;
			for(auto &j : gph[x.second]){
				if(dist[i][j.second] > j.first + x.first){
					dist[i][j.second] = j.first + x.first;
					pq.emplace(dist[i][j.second], j.second);
				}
			}
		}
	}
	vector<pi> cnd;
	vector<lint> vx, vy;
	for(int i=0; i<n; i++){
		lint sx = dist[0][i] + dist[1][i];
		lint sy = dist[0][i] - dist[1][i];
		cnd.emplace_back(sx, sy);
		vx.push_back(sx);
		vy.push_back(sy);
	}
	nth_element(vx.begin(), vx.begin() + n / 2, vx.end());
	nth_element(vy.begin(), vy.begin() + n / 2, vy.end());
	lint dap = 0;
	for(auto &i : cnd){
		dap += abs(i.first - vx[n / 2]) + abs(i.second - vy[n / 2]);
	}
	printf("%.10Lf\n", dap / (2.0L * n));
}

int main(){
		freopen("input.txt", "rb", stdin);
	freopen("output.txt", "wb", stdout);

	int tc; scanf("%d",&tc);
	for(int i=1; i<=tc; i++){
		solve();
	}
}
