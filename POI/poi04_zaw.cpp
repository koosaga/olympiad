#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

struct node{
	int src, pos, dist;
	bool operator<(const node &c)const{
		return dist > c.dist;
	}
};

priority_queue<node> pq;
vector<pi> gph[5005];
int n, m;
int go[5005];
bool vis[5005][2];
node dist[5005][2];

int main(){
	cin >> n >> m;
	for(int i=0; i<m; i++){
		int s, e, x, y;
		cin >> s >> e >> x >> y;
		if(s > e) swap(s, e), swap(x, y);
		gph[s].push_back(pi(x, e));
		gph[e].push_back(pi(y, s));
		if(s == 1) go[e] = y;
	}
	for(int i=0; i<gph[1].size(); i++){
		pq.push({gph[1][i].second, gph[1][i].second, gph[1][i].first});
	}
	while(!pq.empty()){
		node x = pq.top();
		pq.pop();
		if(vis[x.pos][1]) continue;
		else if(vis[x.pos][0]){
			if(dist[x.pos][0].src == x.src) continue;
			vis[x.pos][1] = 1;
			dist[x.pos][1] = x;
		}
		else{
			vis[x.pos][0]= 1;
			dist[x.pos][0] = x;
		}
		for(int ii=0; ii<gph[x.pos].size(); ii++){
			pi i = gph[x.pos][ii];
			if(i.second == 1) continue;
			pq.push({x.src, i.second, i.first + x.dist});
		}
	}
	int ret = 1e9;
	for(int i=0; i<gph[1].size(); i++){
		int pos = gph[1][i].second;
		if(vis[pos][0] && dist[pos][0].src != pos){
			ret = min(ret, go[pos] + dist[pos][0].dist);
		}
		else if(vis[pos][1]){
			ret = min(ret, go[pos] + dist[pos][1].dist);
		}
	}
	cout << ret;
}