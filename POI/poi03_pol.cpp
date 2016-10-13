#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

vector<pi> gph[105];
priority_queue<int> dis[105][105];
int dap[105][105][105];

int n, m, k;

int main(){
	cin >> n >> m;
	for(int i=0; i<m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		gph[s].push_back(pi(x, e));
	}
	memset(dap, -1, sizeof(dap));
	for(int i=1; i<=n; i++){		
		priority_queue<pi, vector<pi>, greater<pi> > pq;
		pq.push(pi(0, i));
		while(!pq.empty()){
			auto x = pq.top();
			pq.pop();
			if(dis[i][x.second].size() && dis[i][x.second].top() < x.first) continue;
			for(auto &j : gph[x.second]){
				pi w(j.first + x.first, j.second);
				if(dis[i][j.second].size() < 100 || dis[i][j.second].top() > w.first){
					dis[i][j.second].push(w.first);
					pq.push(w);
					if(dis[i][j.second].size() > 100) dis[i][j.second].pop();
				}
			}
		}
		for(int j=1; j<=n; j++){
			while(!dis[i][j].empty()){
				dap[i][j][dis[i][j].size()] = dis[i][j].top();
				dis[i][j].pop();
			}
		}
	}
	int q;
	cin >> q;
	while(q--){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		printf("%d\n", dap[s][e][x]);
	}
}

