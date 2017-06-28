#include "Anyalib.h"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;

static int par[505], ia[505], ib[505], dep[505], n;

static vector<int> gph[505];
static vector<pi> el;

static void dfs(int x, int p){
	for(auto &i : gph[x]){
		if(i == p) continue;
		par[i] = x;
		dep[i] = dep[x] + 1;
		el.push_back(pi(x, i));
		dfs(i, x);
		el.push_back(pi(i, x));
	}
}

static int getL;

void InitAnya(int N , int A[] , int B[]) {
	n = N;
	memcpy(ia, A, sizeof(int) * (N-1));
	memcpy(ib, B, sizeof(int) * (N-1));
	for(int i=0; i<N-1; i++){
		gph[ia[i]].push_back(ib[i]);
		gph[ib[i]].push_back(ia[i]);
	}
	dfs(0, -1);
}

int pchk[505], sum[1005];

void Anya(int C[]) {
	for(int i=0; i<n-1; i++){
		Save(i, C[i]);
		if(par[ia[i]] == ib[i]) swap(ia[i], ib[i]);
		pchk[ib[i]] = C[i];
	}
	memset(sum, 0, sizeof(sum));
	for(int i=0; i<el.size(); i++){
		if(dep[el[i].first] < dep[el[i].second]){
			sum[i] = pchk[el[i].second];
		}
		else{
			sum[i] = -pchk[el[i].first];
		}
	}
	for(int i=1; i<=1000; i++) sum[i] += sum[i-1];
	int pnt = n - 1;
	for(int i=19; i<=999; i+=20){
		for(int j=0; j<9; j++){
			Save(pnt++, (sum[i] >> j) & 1);
		}
	}
}


