#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 250005;
using pi = pair<lint, int>;
using pii = pair<pi, int>;

priority_queue<pii, vector<pii>, greater<pii> > pq;
vector<pi> gph[MAXN];
pi dis[MAXN];
int n, m, q;
int s[MAXN], e[MAXN], x[MAXN];
lint ans[MAXN];

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		scanf("%d %d %d",&s[i],&e[i],&x[i]);
		gph[s[i]].push_back(pi(x[i], e[i]));
		gph[e[i]].push_back(pi(x[i], s[i]));
	}
	fill(dis + 1, dis + n + 1, pi(1e18, -1));
	int q; scanf("%d",&q);
	for(int i=0; i<q; i++){
		int x;
		scanf("%d",&x);
		pq.push(pii(pi(0, i), x));
		dis[x] = pi(0, i);
	}
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(dis[x.second] != x.first) continue;
		for(auto &i : gph[x.second]){
			if(dis[i.second] > pi(x.first.first + i.first, x.first.second)){
				dis[i.second] = pi(x.first.first + i.first, x.first.second);
				pq.push(pii(dis[i.second], i.second));
			}
		}
	}
	for(int i=0; i<m; i++){
		lint val = (dis[s[i]].first + dis[e[i]].first + x[i]);
		ans[dis[s[i]].second] += val - 2 * dis[s[i]].first;
		ans[dis[e[i]].second] += val - 2 * dis[e[i]].first;
	}
	for(int i=0; i<q; i++){
		printf("%lld.%lld\n", ans[i] / 2, (ans[i] % 2) * 5);
	}
}
