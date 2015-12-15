#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, m, k, l[40005], r[40005];
vector<int> v1[40005], v2[40005];
vector<int> dp1[40005], dp2[40005];

lint f1(int x, int p);
lint f2(int x, int p);

lint f1(int x, int p){
	if(p < 0) return l[x];
	if(~dp1[x][p]) return dp1[x][p];
	int pos = v1[x][p];
	int low = lower_bound(v2[pos].begin(), v2[pos].end(), x) - v2[pos].begin();
	lint ret = max(f2(pos, low - 1), f1(x, p-1) - l[x]);
	return dp1[x][p] = ret + l[x];
}

lint f2(int x, int p){
	if(p < 0) return r[x];
	if(~dp2[x][p]) return dp2[x][p];
	int pos = v2[x][p];
	int low = lower_bound(v1[pos].begin(), v1[pos].end(), x) - v1[pos].begin();
	lint ret = max(f1(pos, low - 1), f2(x, p-1) - r[x]);
	return dp2[x][p] = ret + r[x];
}

int main(){
	cin >> n >> m >> k;
	for(int i=1; i<=n; i++){
		cin >> l[i];
	}
	for(int i=1; i<=m; i++){
		cin >> r[i];
	}
	for(int i=0; i<k; i++){
		int s, e;
		cin >> s >> e;
		v1[s].push_back(e);
		v2[e].push_back(s);
	}
	for(int i=1; i<=n; i++){
		sort(v1[i].begin(), v1[i].end());
		dp1[i].resize(v1[i].size(), -1);
	}
	for(int i=1; i<=m; i++){
		sort(v2[i].begin(), v2[i].end());
		dp2[i].resize(v2[i].size(), -1);
	}
	lint ret = 0;
	for(int i=1; i<=n; i++){
		ret = max(ret, f1(i, v1[i].size() - 1));
	}
	for(int i=1; i<=m; i++){
		ret = max(ret, f2(i, v2[i].size() - 1));
	}
	cout << ret;
}