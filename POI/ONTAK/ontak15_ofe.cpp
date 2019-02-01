#include <bits/stdc++.h>
#include "ofe.h"
using namespace std;

static int n;
vector<int> loser[10005];

int solve(int s, int e){
	if(s == e) return s;
	int m = (s+e)/2;
	int v = solve(s, m);
	int w = solve(m+1, e);
	if(cmp(w, v)) swap(v, w);
	loser[v].push_back(w);
	return v;
}

int main(){
	n = getN();
	int w = solve(1, n);
	int cur = loser[w][0];
	for(int i=1; i<loser[w].size(); i++){
		if(cmp(loser[w][i], cur)){
			cur = loser[w][i];
		}
	}
	answer(cur);
}
