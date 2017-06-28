#include "Borislib.h"
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

void InitBoris(int N , int A[] , int B[]) {
	memcpy(ia, A, sizeof(int) * (N-1));
	memcpy(ib, B, sizeof(int) * (N-1));
	n = N;
	for(int i=0; i<N-1; i++){
		gph[A[i]].push_back(B[i]);
		gph[B[i]].push_back(A[i]);
	}
	dfs(0, -1);
}

int querya(int x){
	if(x < 0) return 0;
	assert(x % 20 == 19);
	x = 9 * (x / 20) + n-1;
	int ans = 0;
	for(int j=0; j<9; j++){
		ans |= (Ask(x + j) << j);
	}
	return ans;
}

int get_pchk(int node){
	for(int i=0; i<n-1; i++){
		if(par[ia[i]] == ib[i]) swap(ia[i], ib[i]);
		if(ib[i] == node) return Ask(i);
	}
	assert(0);
}

int queryb(int x){
	if(x >= el.size()) return 0;
	if(dep[el[x].first] < dep[el[x].second]){
		return get_pchk(el[x].second);
	}
	else return -get_pchk(el[x].first);
}

int Boris(int city) {
	int gs = 0;
	for(int i=0; i<el.size(); i++){
		if(el[i].second == city){
			gs = i;
			break;
		}
	}
	if(gs % 20 >= 10){
		int up = (gs / 20 + 1) * 20;
		int sum = querya(up - 1);
		for(int i=gs+1; i<up; i++){
			sum -= queryb(i);
		}
		return sum;
	}
	else{
		int up = (gs / 20) * 20;
		int sum = querya(up - 1);
		for(int i=up; i<=gs; i++){
			sum += queryb(i);
		}
		return sum;
	}
}
