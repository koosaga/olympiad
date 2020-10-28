#include "prize.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;

map<int, pi> mp;

pi Ask(int x){
	if(mp.find(x) != mp.end()) return mp[x];
	auto q = ask(x);
	return mp[x] = pi(q[0], q[1]);
}

int find_best(int n) {
	if(n <= 5000){
		for(int i = 0; i < n; i++) {
			std::vector<int> res = ask(i);
			if(res[0] + res[1] == 0)
				return i;
		}
	}
	vector<int> cp;
	for(int i=0; i<=500; i++){
		int w = ((n-1) * i) / 500;
		cp.push_back(w);
	}
	int thres = 0;
	for(auto &i : cp){
		pi p = Ask(i);
		thres = max(thres, p.first + p.second);
	}
	auto abnormal = [&](int x){
		pi p = Ask(x);
		return p.first + p.second != thres;
	};
	for(int i=0; i<n; i++){
		if(abnormal(i)){
			pi p = Ask(i);
			if(p.first + p.second == 0) return i;
		}
		else{
			auto incompatible = [&](int x, int y){
				assert(x < y);
				if(abnormal(y)) return true;
				auto p = Ask(x).second;
				auto q = Ask(y).second;
				return p != q;
			};
			int s = i + 1;
			int e = n + 100;
			for(auto &j : cp){
				if(j > i && incompatible(i, j)){
					e = j;
					break;
				}
				s = max(s, j);
			}
			while(s != e){
				int m = (s + e) / 2;
				if(incompatible(i, m)) e = m;
				else s = m + 1;
			}
			assert(abnormal(s));
			i = s - 1;
		}
	}
	assert(0);
}
