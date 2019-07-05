#include "meetings.h"
#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

mt19937 rng(0x14004);
int randint(int lb, int ub){ return uniform_int_distribution<int>(lb, ub)(rng); }

void bridge(int x, int y){ Bridge(min(x, y), max(x, y)); }

void dfs(vector<int> v){
	if(v.size() == 1) return;
	if(v.size() == 2){
		bridge(v[0], v[1]);
		return;
	}
	map<int, int> mp;
	for(int i=0; i<11; i++){
		set<int> s;
		while(s.size() < 3){
			s.insert(v[randint(0, v.size() - 1)]);
		}
		int x = *s.begin();
		int y = *next(s.begin());
		int z = *next(next(s.begin()));
		int q = Query(x, y, z);
		mp[q]++;
	}
	pi ret(-1, -1);
	for(auto &i : mp){
		ret = max(ret, pi(i.second, i.first));
	}
	int c = ret.second;
	vector<vector<int>> anclist;
	for(auto &i : v){
		if(i == c) continue;
		bool found = 0;
		for(auto &j : anclist){
			if(find(j.begin(), j.end(), i) != j.end()){
				found = 1;
				break;
			}
		}
		if(found) continue;
		for(auto &j : anclist){
			int x = Query(i, j[0], c);
			if(x == c) continue;
			j.push_back(i);
			if(find(j.begin(), j.end(), x) == j.end()) j.push_back(x);
			swap(j[0], *find(j.begin(), j.end(), x));
			found = 1;
			break;
		}
		if(!found){
			anclist.push_back({i});
		}
	}
	for(auto &i : anclist){
		bridge(c, i[0]);
		dfs(i);
	}
}

void Solve(int N) {
	vector<int> v(N);
	iota(v.begin(), v.end(), 0);
	dfs(v);
}