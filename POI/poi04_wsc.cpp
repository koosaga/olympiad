#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

vector<int> gph[1000005];
int sz[1000005], dep[1000005];
int n, e, w;
int cur, pos;

int dfs(int x, int p){
	int ret = (x >= n - w + 1);
	for(auto &i : gph[x]){
		if(i == p) continue;
		dep[i] = dep[x] + 1;
		ret += dfs(i, x);
	}
	if(ret == w && cur < dep[x]){
		cur = dep[x];
		pos = x;
	}
	return sz[x] = ret;
}

int dep2[1000005];

void dfs2(int x, int p){
	for(auto &i : gph[x]){
		if(i == p) continue;
		dep2[i] = dep2[x] + 1;
		dfs2(i, x);
	}
}

vector<int> vl, vr;

int main(){
	cin >> n >> e >> w;
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, 0);
	dfs2(pos, 0);
	for(int i=n-w+1; i<=n; i++){
		vl.push_back(dep2[i]);
	}
	int q;
	scanf("%d",&q);
	for(int i=0; i<q; i++){
		int x;
		scanf("%d",&x);
		vr.push_back(dep2[x]);
	}
	sort(vl.begin(), vl.end());
	sort(vr.begin(), vr.end());
	int low = -1;
	for(int i=0; i<q; i++){
		if(low < vl[i]){
			low = vl[i];
		}
		else{
			low++;
			vl[i] = low;
		}
	}
	low = -1;
	for(int i=0; i<q; i++){
		if(low < vr[i]){
			low = vr[i];
		}
		else{
			low++;
			vr[i] = low;
		}
	}
	int ret = 0;
	for(int i=0; i<q; i++){
		ret = max(ret, vl[i] + vr[q-i-1]);
	}
	cout << ret;
}
