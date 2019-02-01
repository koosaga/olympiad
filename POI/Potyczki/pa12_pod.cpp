#include <bits/stdc++.h>
using namespace std;
const int MAXN = 400005;
typedef long long lint;
typedef pair<lint, lint> pi;

int n, m;
int s[MAXN], e[MAXN], x[MAXN];

struct edg{
	int cost, type, idx;
	bool operator<(const edg &e)const{
		return make_tuple(cost, type, idx) < make_tuple(e.cost, e.type, e.idx);
	}
};

vector<edg> tgph[100005];
vector<pi> gph[2000005];
vector<int> nxt[2000005];

lint dist[2000005];

lint dijkstra(){
	memset(dist, 0x3f, sizeof(dist));
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	for(int i=0; i<2*m; i++){
		if(s[i] == 1){
			dist[i] = x[i];
			pq.push(pi(x[i], i));
		}
	}
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(dist[x.second] != x.first) continue;
		for(auto &i : gph[x.second]){
			if(dist[i.second] > dist[x.second] + i.first){
				dist[i.second] = dist[x.second] + i.first;
				pq.push(pi(dist[i.second], i.second));
			}
		}
	}
	lint ans = 1e18;
	for(int i=0; i<2*m; i++){
		if(e[i] == n) ans = min(ans, x[i] + dist[i]);
	}
	return ans;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int sv, ev, xv;
		scanf("%d %d %d",&sv,&ev,&xv);
		s[2*i] = sv, e[2*i] = ev, x[2*i] = xv;
		s[2*i+1] = ev, e[2*i+1] = sv, x[2*i+1] = xv;
		tgph[sv].push_back({xv, 0, 2*i});
		tgph[ev].push_back({xv, 1, 2*i});
		tgph[ev].push_back({xv, 0, 2*i+1});
		tgph[sv].push_back({xv, 1, 2*i+1});
	}
	for(int i=1; i<=n; i++) sort(tgph[i].begin(), tgph[i].end());
	int idx = 0;
	for(int i=1; i<=n; i++){
		nxt[i].resize(tgph[i].size());
		for(auto &j : nxt[i]) j = idx++;
	}
	assert(2 * m + 2 * idx == 10 * m);
	for(int i=1; i<=n; i++){
		// stuffs between them
		for(int j=1; j<nxt[i].size(); j++){
			int l = 2 * m + nxt[i][j-1] * 2;
			int r = 2 * m + nxt[i][j] * 2;
			gph[l].push_back(pi(0, r));
			gph[r+1].push_back(pi(0, l+1));
		}
	}
	for(int i=0; i<2*m; i++){
		auto l = lower_bound(tgph[s[i]].begin(), tgph[s[i]].end(), (edg){x[i], 0, i});
		int pos = nxt[s[i]][l - tgph[s[i]].begin()];
		gph[pos * 2 + 2 * m].push_back(pi(x[i], i));
		gph[pos * 2 + 1 + 2 * m].push_back(pi(0, i));
		l = lower_bound(tgph[e[i]].begin(), tgph[e[i]].end(), (edg){x[i], 1, i});
		pos = nxt[e[i]][l - tgph[e[i]].begin()];
		gph[i].push_back(pi(0, pos * 2 + 2 * m));
		gph[i].push_back(pi(x[i], pos * 2 + 2 * m + 1));
	}
	cout << dijkstra() << endl;
}
