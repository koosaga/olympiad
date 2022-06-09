#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;
const int MAXN = 250005;
 
vector<lint> dist[MAXN];
vector<int> gph[MAXN];
 
struct node{
	int x, y; lint dist;
	bool operator<(const node &n)const{
		return dist > n.dist;
	}
};
 
void solve(int n, vector<pi> edg, vector<int> v, int s, int e){
	for(auto &[u, v] : edg){
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	for(int i = 0; i < n; i++) sort(all(gph[i]));
	int p = 0;
	vector<pi> cycs;
	for(int i = 0; i < sz(v); i++){
		for(int j = 0; j < v[i]; j++){
			dist[p].resize(v[i], 1e18);
			p++;
			cycs.emplace_back(i, j);
		}
	}
	while(p < n){
		dist[p++].resize(1, 1e18);
		cycs.emplace_back(-1, 0);
	}
	priority_queue<node> pq;
	auto enq = [&](int v, lint d){
		if(sz(dist[v]) > 1 && d % sz(dist[v]) == cycs[v].second) return;
		if(dist[v][d % sz(dist[v])] > d){
			dist[v][d % sz(dist[v])] = d;
			pq.push({v, (int)(d % sz(dist[v])), d});
		}
	};
	enq(s, 0);
	vector<int> visCount(n);
	while(sz(pq)){
		auto x = pq.top(); pq.pop();
		int v = x.x;
		int w = x.y;
		if(dist[v][w] != x.dist) continue;
		enq(v, x.dist + 1);
		visCount[v]++;
		if(sz(dist[v]) == 1){
			for(auto &y : gph[v]){
				if(cycs[v].first >= 0 && 
						cycs[v].first == cycs[y].first && 
						w == cycs[y].second &&
						(w + 1) % sz(dist[v]) == cycs[v].second){
					continue;
				}
				enq(y, x.dist + 1);
				enq(y, x.dist + 1 + ((cycs[y].second - x.dist) % sz(dist[y]) + sz(dist[y])) % sz(dist[y]));
			}
		}
		else{
			vector<int> newList;
			for(auto &y : gph[v]){
				if(cycs[v].first >= 0 && 
						cycs[v].first == cycs[y].first && 
						w == cycs[y].second &&
						(w + 1) % sz(dist[v]) == cycs[v].second){
					newList.push_back(y);
					continue;
				}
				auto promote = [&](lint x, lint cyc, lint m){
					lint T = (x / cyc) * cyc + m;
					while(T < x) T += cyc;
					return T;
				};
				if(sz(dist[y]) == 1){
					enq(y, x.dist + 1);
				}
				// must run
				else if(cycs[v].first != cycs[y].first){
					enq(y, x.dist + 1);
					lint T = promote(x.dist + 1, sz(dist[y]), cycs[y].second);
					if(T % sz(dist[v]) != cycs[v].second){
						enq(y, T + 1);
					}
					else{
						newList.push_back(y);
						lint newDist = promote(T, sz(dist[v]), w);
						enq(y, newDist + 1);
						lint U = promote(newDist + 1, sz(dist[y]), cycs[y].second);
						if(U % sz(dist[v]) != cycs[v].second) enq(y, U + 1);
					}
				}
				else{
					enq(y, x.dist + 1);
					if(cycs[y].second == (cycs[v].second + 1) % sz(dist[v]) ||
							cycs[v].second == (cycs[y].second + 1) % sz(dist[v])){
						newList.push_back(y);
					}
					else{
						lint T = promote(x.dist + 1, sz(dist[y]), cycs[y].second);
						enq(y, T + 1);
					}
				}
			}
			gph[v] = newList;
		}
	}
	lint ans = *min_element(all(dist[e]));
	if(ans < 1e17) cout << ans << "\n";
	else cout << "impossible\n";
}
 
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m; cin >> n >> m;
	vector<pi> edg;
	for(int i = 0; i < m; i++){
		int u, v; cin >> u >> v;
		edg.emplace_back(u-1, v-1);
	}
	vector<int> idx(n, -1);
	int cnt = 0;
	int k; cin >> k;
	vector<int> siz(k);
	for(int i = 0; i < k; i++){
		cin >> siz[i];
		for(int j = 0; j < siz[i]; j++){
			int v; cin >> v;
			idx[v - 1] = cnt++;
		}
	}
	for(int i = 0; i < n; i++){
		if(idx[i] == -1) idx[i] = cnt++;
	}
	for(auto &[u, v] : edg){
		u = idx[u];
		v = idx[v];
	}
	solve(n, edg, siz, idx[0], idx[n - 1]);
}

