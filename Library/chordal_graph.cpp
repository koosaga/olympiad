#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using lint = long long;
using pi = pair<int, int>;


// assume connected simple graph
vector<int> gph[MAXN];
int n, m, cnt[MAXN], idx[MAXN];

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
					puts("0");
					return 0;
				}
			}
		}
	}
	puts("1");
	for(auto &i : ord) printf("%d ", i);
}
