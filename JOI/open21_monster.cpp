#include "monster.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
namespace {

	bool example_variable;
	vector<int> ans, p;
	map<pi, int> mp;
	bool cmp(int x, int y){
		if(mp.find(pi(x, y)) != mp.end()) return mp[pi(x, y)];
		return mp[pi(x, y)] = !Query(x, y);
	}
}  // namespace


void solve(int l, int r){
	if(l == r) return;
	int m = (l + r) / 2;
	solve(l, m); solve(m + 1, r);
	int p1 = l, p2 = m + 1;
	vector<int> dap;
	while(p1 < m+1 && p2 < r+1){
		if(cmp(p[p1], p[p2])){
			dap.push_back(p[p1++]);
		}
		else dap.push_back(p[p2++]);
	}
	while(p1 < m+1) dap.push_back(p[p1++]);
	while(p2 < r+1) dap.push_back(p[p2++]);
	for(int i=l; i<=r; i++) p[i] = dap[i - l];
}

std::vector<int> Solve(int N) {
	p.resize(N);
	iota(all(p), 0);
	solve(0, N - 1);
	vector<vector<int>> cycles;
	for(int i = 0; i < N; ){
		vector<int> cur_stack;
		int e = i;
		while(e < N && e < i + 3){
			cur_stack.push_back(p[e++]);
		}
		while(e < N && !(cmp(p[e - 1], cur_stack[0]) && !cmp(p[e], cur_stack[0]))){
			cur_stack.push_back(p[e++]);
		}
		cycles.push_back(cur_stack);
		i = e;
	}
	bool normal = 0;
	for(int i = 0; i < sz(cycles); i++){
		if(sz(cycles[i]) >= 4){
			vector<int> v;
			for(int j = 0; j < sz(cycles[i]); j++){
				if(cmp(cycles[i][j], cycles[i][(j+2)%sz(cycles[i])])){
					v.push_back(j);
				}
			}
			assert(sz(v) == 2);
			if(v[1] - v[0] != 1) swap(v[0], v[1]);
			rotate(cycles[i].begin(), cycles[i].begin() + v[1] + 1, cycles[i].end());
			int idx = i;
			{
				for(int i = idx + 1; i < sz(cycles); i++){
					for(int j = 0; j < sz(cycles[i]); j++){
						if(!cmp(cycles[i-1][0], cycles[i][j])){
							rotate(cycles[i].begin(), cycles[i].begin() + j + 1, cycles[i].end());
							break;
						}
					}
				}
				for(int i = idx - 1; i >= 0; i--){
					for(int j = 0; j < sz(cycles[i]); j++){
						if(!cmp(cycles[i][j], cycles[i + 1].back())){
							rotate(cycles[i].begin(), cycles[i].begin() + j, cycles[i].end());
							break;
						}
					}
				}
			}
			normal = 1;
			break;
		}
	}
	if(!normal){
		for(int i = 0; i < sz(cycles[0]); i++){
			for(int j = 0; j < sz(cycles[1]); j++){
				if(!cmp(cycles[0][i], cycles[1][j])){
					rotate(cycles[0].begin(), cycles[0].begin() + i, cycles[0].end());
					rotate(cycles[1].begin(), cycles[1].begin() + j + 1, cycles[1].end());
					break;
				}
			}
		}
		for(int i = 2; i < sz(cycles); i++){
			for(int j = 0; j < sz(cycles[i]); j++){
				if(!cmp(cycles[i-1][0], cycles[i][j])){
					rotate(cycles[i].begin(), cycles[i].begin() + j + 1, cycles[i].end());
					break;
				}
			}
		}
	}
	vector<int> ans;
	for(auto &i : cycles){
		reverse(all(i));
		for(auto &j : i) ans.push_back(j);
	}
	{
		vector<int> S(N);
		for(int i = 0; i < N; i++) S[ans[i]] = i;
		return S;
	}
}
