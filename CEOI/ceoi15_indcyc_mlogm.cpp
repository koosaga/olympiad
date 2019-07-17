#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
using lint = long long;
using pi = pair<int, int>;

// the algorithm may be wrong. if you have any ideas for proving / disproving this, please contact me.

vector<int> gph[MAXN];
int n, m, cnt[MAXN], idx[MAXN];
int mark[MAXN], vis[MAXN], par[MAXN];

void report(int x, int y){
	gph[x].erase(find(gph[x].begin(), gph[x].end(), y));
	gph[y].erase(find(gph[y].begin(), gph[y].end(), x));
	for(int i=1; i<=n; i++){
		if(binary_search(gph[i].begin(), gph[i].end(), x) && 
			binary_search(gph[i].begin(), gph[i].end(), y)){
			mark[i] = 1;
		}
	}
	queue<int> que;
	vis[x] = 1;
	que.push(x);
	while(!que.empty()){
		int x = que.front(); que.pop();
		for(auto &i : gph[x]){
			if(!mark[i] && !vis[i]){
				par[i] = x;
				vis[i] = 1;
				que.push(i);
			}
		}
	}
	assert(vis[y]);
	vector<int> v;
	while(y){
		printf("%d ", y);
		y = par[y];
	}
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	for(int i=1; i<=n; i++) sort(gph[i].begin(), gph[i].end());
	priority_queue<pi> pq;
	for(int i=1; i<=n; i++) pq.emplace(cnt[i], i);
	vector<int> ord;
	while(!pq.empty()){
		int x = pq.top().second, y = pq.top().first;
		pq.pop();
		if(cnt[x] != y || idx[x]) continue;
		ord.push_back(x);
		idx[x] = n + 1 - ord.size();
		for(auto &i : gph[x]){
			if(!idx[i]){
				cnt[i]++;
				pq.emplace(cnt[i], i);
			}
		}
	}
	reverse(ord.begin(), ord.end());
	for(auto &i : ord){
		int minBef = 1e9;
		for(auto &j : gph[i]){
			if(idx[j] > idx[i]) minBef = min(minBef, idx[j]);
		}
		minBef--;
		if(minBef < n){
			minBef = ord[minBef];
			for(auto &j : gph[i]){
				if(idx[j] > idx[minBef] && !binary_search(gph[minBef].begin(), gph[minBef].end(), j)){
					report(minBef, i);
					return 0;
				}
			}
		}
	}
	puts("no");
}


