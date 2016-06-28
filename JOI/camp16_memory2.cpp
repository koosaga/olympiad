#include "Memory2_lib.h"
#include <bits/stdc++.h>
using namespace std;

struct qry{
	int l, r, q;
}a[55];

int dp[105][105];

int get(int a, int b){
	if(~dp[a][b]) return dp[a][b];
	return dp[a][b] = Flip(a, b);
}

void Solve(int T, int N){
	memset(dp, -1, sizeof(dp));
	for(int i=0; i<N; i++){
		a[i] = {2*i, 2*i+1, get(2*i, 2*i+1)};
	}
	for(int i=0; i<N; i++){
		int occs[55] = {};
		for(int j=0; j<N-i; j++){
			occs[a[j].q]++;
		}
		int p = max_element(occs, occs + N) - occs;
		if(occs[p] == 1){
			for(int j=0; j<N-i; j++){
				Answer(a[j].l, a[j].r, a[j].q);
			}
			return;
		}
		else{
			vector<qry> x, y;
			for(int j=0; j<N-i; j++){
				if(a[j].q == p){
					x.push_back(a[j]);
				}
				else{
					y.push_back(a[j]);
				}
			}
			if(get(x[0].l, x[1].l) != p){
				y.push_back({x[0].l, x[1].l, get(x[0].l, x[1].l)});
				Answer(x[0].r, x[1].r, p);
			}
			else if(get(x[0].l, x[1].r) != p){
				y.push_back({x[0].l, x[1].r, get(x[0].l, x[1].r)});
				Answer(x[0].r, x[1].l, p);
			}
			else if(get(x[0].r, x[1].l) != p){
				y.push_back({x[0].r, x[1].l, get(x[0].r, x[1].l)});
				Answer(x[0].l, x[1].r, p);
			}
			else{
				y.push_back({x[0].r, x[1].r, get(x[0].r, x[1].r)});
				Answer(x[0].l, x[1].l, p);
			}
			int pnt = 0;
			for(auto &i : y){
				a[pnt++] = i;
			}
		}
	}
}
