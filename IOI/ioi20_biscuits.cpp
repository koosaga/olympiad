#include "biscuits.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;

long long count_tastiness(long long x, std::vector<long long> a){
	vector<lint> thres;
	a.resize(60);
	lint ret = 0;
	for(int i = 0; i < sz(a); i++){
		ret += (a[i] << i);
		thres.push_back(ret / x);
	}
	vector<pi> cur;
	cur = {pi((1ll << 60) - 1, 1)};
	for(int i = sz(a) - 1; i >= 0; i--){
		vector<pi> nxt;
		for(auto &j : cur) j.first = min(j.first, thres[i]);
		for(auto &j : cur){
			if(j.first >= (1ll << i)){
				nxt.emplace_back(j.first - (1ll << i), j.second);
				nxt.emplace_back((1ll << i) - 1, j.second);
			}
			else{
				nxt.emplace_back(j.first, j.second);
			}
		}
		sort(all(nxt));
		cur.clear();
		for(auto &i : nxt){
			if(sz(cur) && cur.back().first == i.first){
				cur.back().second += i.second;
			}
			else cur.push_back(i);
		}
	}
	ret = 0;
	for(auto &i : cur) ret += i.second;
	return ret;
}

