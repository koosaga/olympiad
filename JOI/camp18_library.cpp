#include <bits/stdc++.h>
#include "library.h"
using namespace std;
const int MAXN = 1005;

int n;
int dp[MAXN][MAXN];

int query(int s, int e){
	if(s > e) return 0;
	if(dp[s][e]) return dp[s][e];
	vector<int> v(n);
	fill(v.begin() + s, v.begin() + e + 1, 1);
	return dp[s][e] = Query(v);
}

vector<int> gph[MAXN];
vector<int> dfn;

void dfs(int x, int p){
	dfn.push_back(x + 1);
	for(auto &i : gph[x]){
		if(i != p){
			dfs(i, x);
		}
	}
}

void Solve(int N){
	if(N == 1){
		Answer({1});
		return;
	}
	n = N;
	for(int i=1; i<N; i++){
		int interesting = query(0, i - 1) + 1 - query(0, i);
		for(int j=0; j<interesting; j++){
			int s = 1, e = i;
			while(s != e){
				int m = (s + e) / 2;
				if(query(m, i) >= query(m, i - 1) + 1 - j){
					e = m;
				}
				else s = m + 1;
			}
			gph[i].push_back(s - 1);
			gph[s - 1].push_back(i);
		//	printf("has edge %d %d\n", s - 1, i);
		}
	}
	for(int i=0; i<N; i++){
		if(gph[i].size() == 1){
			dfs(i, -1);
			break;
		}
	}
	Answer(dfn);
}
