#include "dango3.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

namespace {
	void solve(vector<int> ans, int sz){
		if(sz == 1) Answer(ans);
		else{
			int m = sz / 2;
			vector<int> mark(sz(ans));
			for(int i = 0; i < sz(ans); i++){
				vector<int> nxt;
				for(int j = 0; j < sz(ans); j++){
					if(j != i && !mark[j]) nxt.push_back(ans[j]);
				}
				if(Query(nxt) >= m) mark[i] = 1;
			}
			vector<int> l, r;
			for(int i = 0; i < sz(ans); i++){
				if(mark[i]) l.push_back(ans[i]);
				else r.push_back(ans[i]);
			}
			solve(l, sz - m);
			solve(r, m);
		}
	}
}  // namespace

void Solve(int N, int M) {
	vector<int> ans(N * M); iota(all(ans), 1);
	solve(ans, M);
}
