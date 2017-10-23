#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

int dist[11][30005];
int n, m, a[30005];
vector<pi> gph[30005];

bool pareto_optimal(int pos, int r, int d){
	return r == 10 || dist[r+1][pos] > d;
}

int main(){
	cin >> n >> m;
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	for(int i=0; i<m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		gph[s].push_back(pi(x, e));
		gph[e].push_back(pi(x, s));
	}
	memset(dist, 0x3f, sizeof(dist));
	for(int i=10; i; i--){
		priority_queue<pi, vector<pi>, greater<pi> > pq;
		for(int j=1; j<=n; j++){
			if(a[j] == i){
				dist[i][j] = 0;
				pq.push(pi(0, j));
			}
		}
		while(!pq.empty()){
			auto x = pq.top();
			pq.pop();
			if(dist[i][x.second] != x.first) continue;
			for(auto &j : gph[x.second]){
				if(dist[i][j.second] > x.first + j.first){
					dist[i][j.second] = x.first + j.first;
					pq.push(pi(dist[i][j.second], j.second));
				}
			}
		}
	}
	for(int i=9; i; i--){
		for(int j=1; j<=n; j++){
			dist[i][j] = min(dist[i][j], dist[i+1][j]);
		}
	}
	int ret = 0;
	for(int i=1; i<=n; i++){
		priority_queue<pi, vector<pi>, greater<pi> > pq;
		vector<int> mod = {i};
		dist[0][i] = 0;
		pq.push(pi(0, i));
		while(!pq.empty()){
			auto x = pq.top();
			pq.pop();
			if(dist[0][x.second] != x.first) continue;
			ret++;
			mod.push_back(x.second);
			for(auto &j : gph[x.second]){
				if(pareto_optimal(j.second, a[i], x.first + j.first) && dist[0][j.second] > x.first + j.first){
					dist[0][j.second] = x.first + j.first;
					pq.push(pi(dist[0][j.second], j.second));
				}
			}
		}
		for(auto &i : mod) dist[0][i] = 1e9;
	}
	cout << ret;
}
