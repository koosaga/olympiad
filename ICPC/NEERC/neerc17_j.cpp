#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, int>;
const int MAXN = 3005;

int n, m, k;
int s[MAXN], e[MAXN], x[MAXN];
vector<int> clist;
vector<pi> gph[MAXN];
lint dp[2][MAXN];

lint solve(int c){
	for(int i=1; i<=n; i++) gph[i].clear();
	for(int i=0; i<m; i++){
		gph[s[i]].push_back(pi(max(0, x[i] - c), e[i]));
		gph[e[i]].push_back(pi(max(0, x[i] - c), s[i]));
	}
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	lint dist[MAXN];
	memset(dist, 0x3f, sizeof(dist));
	pq.push(pi(0, 1));
	dist[1] = 0;
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(dist[x.second] != x.first) continue;
		for(auto &j : gph[x.second]){
			if(dist[j.second] > x.first + j.first){
				dist[j.second] = x.first + j.first;
				pq.push(pi(x.first + j.first, j.second));
			}
		}
	}
	return dist[n];
}

lint bellman(){
	memset(dp, 0x3f, sizeof(dp));
	dp[0][1] = 0;
	for(int i=0; i<m; i++){
		gph[s[i]].push_back(pi(x[i], e[i]));
		gph[e[i]].push_back(pi(x[i], s[i]));
	}
	lint ans = 1e18;
	for(int i=0; i<k; i++){
		memset(dp[(i+1)%2], 0x3f, sizeof(dp[0]));
		for(int j=1; j<=n; j++){
			for(auto &k : gph[j]){
				dp[(i+1)%2][k.second] = 
					min(dp[(i+1)%2][k.second], dp[i%2][j] + k.first);
			}
		}
		ans = min(ans, dp[(i+1)%2][n]);
	}
	return ans;
}

int main(){
	cin >> n >> m >> k;
	for(int i=0; i<m; i++){
		cin >> s[i] >> e[i] >> x[i];
		clist.push_back(x[i]);
	}
	sort(clist.begin(), clist.end());
	lint ans = bellman();
	for(auto &i : clist){
		ans = min(ans, solve(i) + 1ll * k * i);
	}
	cout << ans << endl;
}
