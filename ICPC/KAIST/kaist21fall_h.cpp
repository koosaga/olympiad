#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, int>;

int main(){
	int n, m; lint t;
	scanf("%d %d %lld",&n,&m,&t);
	vector<vector<pi>> gph(n, vector<pi>());

	for(int i = 0; i < m; i++){
		int l, r; scanf("%d %d",&l,&r);
		gph[r - 1].emplace_back(i, l - 1);
	}
	vector<int> a(n);
	for(int i = 0; i < n; i++) scanf("%d",&a[i]);
	vector<int> ret(n);
	for(int i = 0; i < 8; i++){
		vector<lint> dist(n, 2e18);
		queue<int> que;
		vector<bool> inque(n);
		auto enq = [&](int x, lint v){
			if(dist[x] > v){
				dist[x] = v;
				if(!inque[x]){
					inque[x] = 1;
					que.push(x);
				}
			}
		};
		for(int j = 0; j < n; j++){
			if((a[j] >> i) & 1) enq(j, 0);
		}
		while(sz(que)){
			int x = que.front(); que.pop();
			inque[x] = 0;
			for(auto &[idx, y] : gph[x]){
				int delta = idx % m - dist[x] % m;
				if(delta < 0) delta += m;
				enq(y, delta + dist[x]+ 1);
			}
		}
		for(int j = 0; j < n; j++) if(dist[j] <= t) ret[j] |= (1<<i);
	}
	for(auto &i : ret) printf("%d ", i);
}
