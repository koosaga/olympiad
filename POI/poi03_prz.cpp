#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;
using lint = long long;
const int MAXN = 10005;

int n, m;
vector<pi> gph[MAXN];
int dist[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		int v; scanf("%d",&v);
		gph[2*i].emplace_back(v/2, 2*i+1);
	}
	scanf("%d",&m);
	for(int i=0; i<m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		s--, e--;
		gph[2*s].emplace_back(x, 2*e);
		gph[2*s+1].emplace_back(x, 2*e+1);
	}
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	pq.emplace(0, 0);
	memset(dist, 0x3f, sizeof(dist));
	dist[0] = 0;
	while(!pq.empty()){
		auto x = pq.top(); pq.pop();
		if(dist[x.second] != x.first) continue;
		for(auto &i : gph[x.second]){
			if(dist[i.second] > x.first + i.first){
				dist[i.second] = x.first + i.first;
				pq.emplace(dist[i.second], i.second);
			}
		}
	}
	cout << dist[1] << endl;
}
