#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 9;

vector<pi> gph[100005];
lint dist[100005], dp[100005];
int n, m, s, e;

int main(){
	memset(dist, 0x3f, sizeof(dist));
	scanf("%d %d %d %d",&n,&m,&s,&e);
	for(int i=0; i<m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		gph[s].push_back(pi(x, e));
		gph[e].push_back(pi(x, s));
	}
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	dist[s] = 0;
	pq.push(pi(0, s));
	vector<int> ord;
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(dist[x.second] != x.first) continue;
		ord.push_back(x.second);
		for(auto &i : gph[x.second]){
			if(dist[i.second] > x.first + i.first){
				dist[i.second] = x.first + i.first;
				pq.push(pi(dist[i.second], i.second));
			}
		}
	}
	dp[s] = 1;
	for(auto &i : ord){
		dp[i] %= mod;
		for(auto &j : gph[i]){
			if(dist[j.second] == dist[i] + j.first){
				dp[j.second] += dp[i];
			}
		}
	}
	cout << dp[e] << endl;
}
