#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

vector<int> gph[50005];
set<pi> edgs;
bool vis[50005];
int deg[50005];
int n;

int main(){
	scanf("%d %*d",&n);
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	for(int i=0; i<n; i++){
		scanf("%d",&deg[i]);
		gph[i].resize(deg[i]);
		pq.push(pi(deg[i], i));
		for(auto &j : gph[i]){
			scanf("%d",&j);
			edgs.insert(pi(i, j));
		}
	}
	int ans = 0;
	while(true){
		while(!pq.empty() && vis[pq.top().second]) pq.pop();
		if(pq.empty()) break;
		int w = pq.top().second;
		vis[w] = 1;
		deg[w] = 0;
		pq.pop();
		vector<int> v = {w};
		for(auto &j : gph[w]){
			if(!vis[j]){
				deg[j]--;
				pq.push(pi(deg[j], j));
				v.push_back(j);
			}
		}
		vis[w] = 1;
		bool adj[11][11] = {};
		for(int i=0; i<v.size(); i++){
			adj[i][i] = 1;
			for(int j=0; j<v.size(); j++){
				if(i != j && edgs.find(pi(v[i], v[j])) != edgs.end()){
					adj[i][j] = 1;
				}
			}
		}
		for(int i=1; i<(1<<v.size()); i+=2){
			bool ok = 1;
			int cnt = 0;
			for(int j=0; j<v.size(); j++){
				if((i >> j) % 2 == 0) continue;
				cnt++;
				for(int k=0; k<v.size(); k++){
					if((i >> k) % 2 == 0) continue;
					if(adj[j][k] == 0) ok = 0;
				}
			}
			if(ok) ans = max(ans, cnt);
		}
	}
	cout << ans;
}
