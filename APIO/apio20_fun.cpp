#include "fun.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 505;
const int mod = 1e9 + 7;

vector<int> createFunTour(int N, int Q) {
	int n = N;
	vector<int> dist(n);
	pi dap(1e9, 1e9);
	for(int i=0; i<n; i++){
		int foo = attractionsBehind(0, i);
		if(2 * foo > n){
			dap = min(dap, pi(foo, i));
		}
	}
	int C = dap.second;
	vector<int> adj;
	for(int i=0; i<n; i++){
		dist[i] = hoursRequired(C, i);
		if(dist[i] == 1) adj.push_back(i);
	}
	vector<int> sons[3];
	for(int i=0; i<n; i++){
		if(i == C) continue;
		int put = 0;
		for(int j=1; j<sz(adj); j++){
			if(hoursRequired(adj[j], i) == dist[i] - 1){
				put = j;
				break;
			}
		}
		sons[put].push_back(i);
	}
	for(int i=0; i<sz(adj); i++){
		sort(all(sons[i]), [&](const int &a, const int &b){
			return dist[a] < dist[b];
		});
	}
	vector<int> ans;
	auto majority = [&](){
		int sum = sz(sons[0]) + sz(sons[1]) + sz(sons[2]);
		for(int i=0; i<3; i++){
			if(sz(sons[i]) * 2 >= sum) return i;
		}
		return -1;
	};
	int prv = -1;
	if(majority() == -1){
		while(true){
			vector<int> v;
			for(int j=0; j<sz(adj); j++){
				assert(sz(sons[j]));
				v.push_back(j);
			}
			sort(all(v), [&](const int &a, const int &b){
				int da = dist[sons[a].back()];
				int db = dist[sons[b].back()];
				if(da != db) return da > db;
				return (a != prv) > (b != prv);
			});
			if(v[0] == prv) prv = v[1]; 
			else prv = v[0];
			assert(sz(sons[prv]));
			ans.push_back(sons[prv].back());
			sons[prv].pop_back();
			if(prv == v[0] && majority() != -1) break;
		}
	}
	int foo = sz(ans);
	int w = majority();
	vector<pi> x, y;
	for(int i=0; i<3; i++){
		for(auto &j : sons[i]){
			if(i == w) x.emplace_back(j, i);
			else y.emplace_back(j, i);
		}
	}
	auto cmp = [&](const pi &a, const pi &b){
		if(dist[a.first] != dist[b.first]){
			return dist[a.first] > dist[b.first];
		}
		return (a.second != prv) < (b.second != prv);
	};
	assert(abs(sz(x) - sz(y)) <= 1);
	sort(all(x), cmp);
	sort(all(y), cmp);
	if(sz(x) && sz(y) && x[0].first < y[0].first) swap(x, y);
	if(sz(x) && x[0].second == prv) swap(x, y);
	if(sz(x) <= sz(y)) x.emplace_back(C, -1);
	else y.emplace_back(C, -1);
	for(int i=0; i<sz(x); i++){
		ans.push_back(x[i].first);
		if(i < sz(y)) ans.push_back(y[i].first);
	}
	/*
	for(int i=2; i<sz(ans); i++){
		if(hoursRequired(ans[i-2], ans[i-1]) < hoursRequired(ans[i-1], ans[i])){
			puts("---");
			cout << foo << endl;
			for(auto &j : ans) printf("%d " , j);
			puts("");
		}
	}*/
	return ans;
}
