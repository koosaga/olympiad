#include "prison.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

vector<vector<int>> ans;
void solve(int s, int e, int pos, int who){
	if(s > e) return;
	ans[pos][0] = who;
	int cp = pos;
	while(cp % 3) cp++;
	vector<pi> intv;
	if(cp == 18){
		intv.emplace_back(s+1, (s+e)/2);
		if(intv.back().first > intv.back().second) intv.pop_back();
		intv.emplace_back((s+e)/2+1, e-1);
		if(intv.back().first > intv.back().second) intv.pop_back();
	}
	else{
		int m1 = (s * 2 + e + 1) / 3;
		int m2 = (s + e * 2 - 1) / 3;
		intv.emplace_back(s + 1, m1);
		if(intv.back().first > intv.back().second) intv.pop_back();
		intv.emplace_back(m1 + 1, m2);
		if(intv.back().first > intv.back().second) intv.pop_back();
		intv.emplace_back(m2 + 1, e-1);
		if(intv.back().first > intv.back().second) intv.pop_back();
	}
	for(int i = s; i <= e; i++){
		if(i == s) ans[pos][i] = (who ? -2 : -1);
		else if(i == e) ans[pos][i] = (who ? -1 : -2);
		else{
			for(int j = 0; j < sz(intv); j++){
				if(intv[j].first <= i && i <= intv[j].second) ans[pos][i] = cp + 1 + j;
			}
		}
	}
	for(int i = 0; i < sz(intv); i++){
		for(int j = s; j <= intv[i].first - 1; j++){
			ans[cp + 1 + i][j] = (who ? -1 : -2);
		}
		for(int j = intv[i].second + 1; j <= e; j++){
			ans[cp + 1 + i][j] = (who ? -2 : -1);
		}
		solve(intv[i].first, intv[i].second, cp + 1 + i, who ^ 1);
	}
}

std::vector<std::vector<int>> devise_strategy(int N) {
	ans.resize(21, vector<int>(N + 1));
	solve(1, N, 0, 0);
	return ans;
}
