#include "Encoder.h"
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 250005;

vector<int> generate_seq(){
	double rat = 1.05;
	vector<int> v = {1};
	while(v.size() < 256){
		int curV = (int)round(rat);
		if(curV != v.back()) v.push_back(curV);
		rat *= 1.05;
	}
	return v;
}

vector<int> seq;
vector<int> gph[MAXN];
int dfn[MAXN], sz[MAXN], piv;

void dfs(int x, int p){
	sz[x] = 1;
	dfn[x] = ++piv;
	for(auto &i : gph[x]){
		if(i != p){
			dfs(i, x);
			sz[x] += sz[i];
		}
	}
	while(!binary_search(seq.begin(), seq.end(), sz[x])){
		sz[x]++;
		piv++;
	}
}

void Encode(int N, int A[], int B[]){
	for(int i=0; i<N-1; i++){
		gph[A[i]].push_back(B[i]);
		gph[B[i]].push_back(A[i]);
	}
	seq = generate_seq();
	dfs(0, -1);
	for (int i = 0; i < N; ++i) {
		sz[i] = lower_bound(seq.begin(), seq.end(), sz[i]) - seq.begin();
		Code(i, ((long long)dfn[i] << 8) + sz[i]);
	}
}
