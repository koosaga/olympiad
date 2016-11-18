#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

struct edg{
	int pos, cst;
	lint dist;
	bool operator<(const edg &e)const{
		return dist > e.dist;
	}
};

bool vis[2505][2505];
priority_queue<edg> pq;
vector<pi> gph[2505];
int n, m, a[2505];

int main(){
	cin >> n >> m;
	for(int i=1; i<=n; i++) cin >> a[i];
	for(int i=0; i<m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		gph[s].push_back(pi(x, e));
		gph[e].push_back(pi(x, s));
	}
	pq.push({1, a[1], 0});
	while(!pq.empty()){
		auto w = pq.top();
		pq.pop();
		if(vis[w.pos][w.cst]) continue;
		if(w.pos == n){
			cout << w.dist;
			return 0;
		}
		vis[w.pos][w.cst] = 1;
		for(auto &i : gph[w.pos]){
			pq.push({i.second, min(w.cst, a[i.second]), w.cst * i.first + w.dist});
		}
	}
	assert(0);
}
