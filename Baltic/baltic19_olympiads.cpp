#include <bits/stdc++.h>
using namespace std;
const int MAXN = 505;
using lint = long long;
using pi = pair<lint, int>;

int n, k, c;
int a[MAXN][10];
priority_queue<int, vector<int>, greater<int> > ans;
set<vector<int>> vis;
vector<int> gph[MAXN];

int cost(vector<int> &x){
	int ax[10] = {};
	for(auto &i : x){
		for(int j=0; j<k; j++) ax[j] = max(ax[j], a[i][j]);
	}
	return accumulate(ax, ax + k, 0);
}

auto cmp = [](vector<int> &x, vector<int> &y){
	return cost(x) < cost(y);
};

priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);

int main(){
	cin >> n >> k >> c;
	for(int i=1; i<=n; i++){
		for(int j=0; j<k; j++){
			cin >> a[i][j];
		}
	}
	vector<int> cnd;
	for(int i=0; i<k; i++){
		vector<pi> v;
		for(int j=1; j<=n; j++){
			v.emplace_back(a[j][i], j);
		}
		sort(v.rbegin(), v.rend());
		cnd.push_back(v[0].second);
		for(int j=1; j<=n; j++){
			gph[j].push_back(v[0].second);
		}
		for(int j=1; j<n; j++){
			gph[v[j-1].second].push_back(v[j].second);
		}
	}
	sort(cnd.begin(), cnd.end());
	cnd.resize(unique(cnd.begin(), cnd.end()) - cnd.begin());
	for(int i=1; i<=n; i++){
		if(cnd.size() < k && find(cnd.begin(), cnd.end(), i) == cnd.end()) cnd.push_back(i);
	}
	sort(cnd.begin(), cnd.end());
	vis.insert(cnd);
	pq.push(cnd);
	for(int i = 0; i < c - 1; i++){
		auto x = pq.top();
		pq.pop();
		/*
		printf("[");
		for(auto &i : x) printf("%d", i);
		puts("]");
		printf("%lld\n", cost(x));*/
		for(int i=0; i<k; i++){
			for(auto &j : gph[x[i]]){
				auto nxt = x;
				nxt[i] = j;
				sort(nxt.begin(), nxt.end());
				bool good = 1;
				for(int j=1; j<k; j++){
					if(nxt[j-1] == nxt[j]) good = 0;
				}
				if(!good) continue;
				if(vis.find(nxt) == vis.end()){
					pq.push(nxt);
					vis.insert(nxt);
				}
			}
		}
	}
	auto x = pq.top();
	printf("%d\n", cost(x));
}


