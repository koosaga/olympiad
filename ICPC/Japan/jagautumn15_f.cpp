#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 10005;

vector<int> g0[MAXN];
vector<int> g1[MAXN];
int n, a, b, c, d[6][MAXN], v[3], p[MAXN];

void bfs2(int *d){
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	for(int i=1; i<=n; i++){
		pq.push(pi(d[i], i));
	}
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(d[x.second] != x.first) continue;
		for(auto &i : g0[x.second]){
			if(d[i] > x.first){
				d[i] = x.first;
				pq.push(pi(x.first, i));
			}
		}
		for(auto &i : g1[x.second]){
			if(d[i] > x.first + 1){
				d[i] = x.first + 1;
				pq.push(pi(x.first + 1, i));
			}
		}
	}
}

void bfs(int x, int *d){
	if(x < 0){
		bfs2(d);
		return;
	}
	bool proc[MAXN] = {};
	deque<int> dq;
	dq.push_back(x);
	d[x] = 0;
	while(!dq.empty()){
		int x = dq.front();
		dq.pop_front();
		if(proc[x]) continue;
		proc[x] = 1;
		for(auto &i : g0[x]){
			if(d[i] > d[x]){
				d[i] = d[x];
				dq.push_front(i);
			}
		}
		for(auto &i : g1[x]){
			if(d[i] > d[x] + 1){
				d[i] = d[x] + 1;
				dq.push_back(i);
			}
		}
	}
}

int main(){
	scanf("%d %d %d %d",&n,&a,&b,&c);
	for(int i=0; i<a; i++){
		scanf("%d",&p[i]);
		if(i > 0){
			g0[p[i-1]].push_back(p[i]);
			g0[p[i]].push_back(p[i-1]);
		}
		v[0] = p[i];
	}
	for(int i=0; i<b; i++){
		scanf("%d",&p[i]);
		if(i > 0){
			g0[p[i-1]].push_back(p[i]);
			g0[p[i]].push_back(p[i-1]);
		}
		v[1] = p[i];
	}
	for(int i=0; i<c; i++){
		scanf("%d",&p[i]);
		if(i > 0){
			g0[p[i-1]].push_back(p[i]);
			g0[p[i]].push_back(p[i-1]);
		}
		v[2] = p[i];
	}
	int m;
	scanf("%d",&m);
	while(m--){
		int s, e;
		scanf("%d %d",&s,&e);
		g1[s].push_back(e);
		g1[e].push_back(s);
	}
	memset(d, 0x3f, sizeof(d));
	for(int i=0; i<3; i++) bfs(v[i], d[i]);
	for(int i=1; i<=n; i++){
		d[3][i] = d[0][i] + d[1][i];
		d[4][i] = d[0][i] + d[2][i];
		d[5][i] = d[1][i] + d[2][i];
	}
	for(int i=3; i<6; i++) bfs(-1, d[i]);
	pi ret(1e9, 1e9);
	for(int i=1; i<=n; i++){
		int ans = min({d[3][i] + d[2][i], d[4][i] + d[1][i], d[5][i] + d[0][i]});
		ret = min(ret, pi(ans, i));
	}
	cout << ret.first << " " << ret.second << endl;
}
