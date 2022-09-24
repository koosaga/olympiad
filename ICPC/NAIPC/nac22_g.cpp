#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 250005;

vector<int> gph[MAXN];
int dx[256], dy[256];

int din[MAXN], dout[MAXN], piv, par[MAXN];
int indeg[MAXN], trueIdx[MAXN];

void dfs(int x){
	din[x] = ++piv;
	for(auto &y : gph[x]) dfs(y);
	dout[x] = piv;
}

int diff[MAXN], good[MAXN];

int main(){	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	dx['^'] = -1;
	dx['v'] = +1;
	dy['<'] = -1;
	dy['>'] = +1;
	int n, m; cin >> n >> m;
	vector<string> str(n);
	for(int i = 0; i < n; i++) cin >> str[i];
	good[0] = 1;
	auto idx = [&](int p, int q){
		if(p < 0 || p >= n || q < 0 || q >= m) return 0;
		if(str[p][q] == '.' || str[p][q] == '#') return 0;
		return p * m + q + 1;
	};
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(str[i][j] == '.' || str[i][j] == '#') continue;
			int cur = idx(i, j);
			int nxt = idx(i + dx[str[i][j]], j + dy[str[i][j]]);
			good[cur] = 1;
			gph[nxt].push_back(cur);
			par[cur] = nxt;
			indeg[nxt]++;
		}
	}
	queue<int> que;
	for(int i = 0; i <= n * m; i++){
		if(good[i] && !indeg[i]){
			que.push(i);
		}
	}
	while(sz(que)){
		int x = que.front();
		que.pop();
		trueIdx[x] = x;
		if(x != 0){
			indeg[par[x]]--;
			if(indeg[par[x]] == 0) que.push(par[x]);
		}
	}
	for(int i = 0; i <= n * m; i++){
		if(indeg[i]){
			int idx = i;
			for(int j = i; indeg[j]; j = par[j]){
				trueIdx[j] = idx;
				indeg[j] = 0;
			}
			gph[par[i]].erase(find(all(gph[par[i]]), i));
			dfs(i);
		}
	}
	dfs(0);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(str[i][j] == '#'){
				vector<pi> events;
				for(auto &k : "^v<>"){
					int nxt = idx(i + dx[k], j + dy[k]);
					if(nxt == 0) continue;
					int vtx = trueIdx[nxt];
					events.emplace_back(din[vtx], +1);
					events.emplace_back(dout[vtx] + 1, -1);
				}
				sort(all(events));
				int sum = 0;
				for(int i = 0; i < sz(events) - 1; i++){
					sum += events[i].second;
					if(sum > 0){
						diff[events[i].first]++;
						diff[events[i + 1].first]--;
					}
				}
			}
		}
	}
	for(int i = 1; i <= piv; i++) diff[i] += diff[i-1];
	cout << *max_element(diff, diff + piv + 1) << "\n";
}
