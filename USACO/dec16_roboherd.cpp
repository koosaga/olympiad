#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, k;
vector<vector<int> > v;
vector<lint> dap;

void solve(){
	lint tot = 0;
	for(int i=0; i<n; i++) tot += v[i][0];

	auto cmp = [&](const vector<pi> &p, const vector<pi> &q){
		lint r1 = 0, r2 = 0;
		for(auto &i : p){
			r1 += v[i.first][i.second] - v[i.first][0];
		}
		for(auto &i : q){
			r2 += v[i.first][i.second] - v[i.first][0];
		}
		return r1 > r2;
	};

	priority_queue<vector<pi>, vector<vector<pi>>, decltype(cmp)> pq(cmp);
	set<vector<pi>> vis;

	vector<pi> w;
	for(int j=0; j<16 && j<n; j++){
		w.push_back(pi(j, 1));
		pq.push(w);
	}
	
	while(!pq.empty() && dap.size() < k){
		auto cur = pq.top();
		pq.pop();
		if(vis.find(cur) != vis.end()) continue;
		vis.insert(cur);
		lint ret = tot;
		for(auto &i : cur){
			ret += v[i.first][i.second] - v[i.first][0];
		}
		dap.push_back(ret);
		for(int i=0; i<cur.size(); i++){
			auto nxt = cur;
			if(nxt[i].second + 1 < v[nxt[i].first].size()){
				nxt[i].second++;
				pq.push(nxt);
				nxt[i].second--;
			}
			if(nxt[i].second == 1 && i + 1 < cur.size() && nxt[i].first + 1 < nxt[i+1].first){
				nxt[i].first++;
				pq.push(nxt);
				nxt[i].first--;
			}
			if(nxt[i].second == 1 && i + 1 == cur.size() && nxt[i].first + 1 < n){
				nxt[i].first++;
				pq.push(nxt);
				nxt[i].first--;
			}
		}
	}
}

int main(){
	cin >> n >> k;
	lint ret = 0;
	dap.push_back(0);
	for(int i=0; i<n; i++){
		int x;
		scanf("%d",&x);
		vector<int> w(x);
		for(int j=0; j<x; j++){
			scanf("%d",&w[j]);
		}
		if(x == 1){
			ret += 1ll * w[0] * k;
		}
		else{
			sort(w.begin(), w.end());
			v.push_back(w);
			dap[0] += w[0];
		}
	}
	sort(v.begin(), v.end(), [&](const vector<int> &a, const vector<int> &b){
		return a[1] - a[0] < b[1] - b[0];
	});
	n = v.size();
	solve();
	for(int i=0; i<k; i++) ret += dap[i];
	cout << ret;
}
