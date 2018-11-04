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

int n;
vector<int> coord[100005];
pi ret[100005];

void solve(){
	scanf("%d",&n);
	int mx = 0;
	for(int i=0; i<n; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		coord[x].push_back(y);
		mx = max(x, mx);
	}
	for(int i=0; i<=mx; i++){
		sort(coord[i].begin(), coord[i].end());
	}
	int py = 0, p = 0;
	for(int i=0; i<=mx; i++){
		if(coord[i].empty()) continue;
		if(coord[i][0] != py){
			reverse(coord[i].begin(), coord[i].end());
		}
		for(auto &j : coord[i]){
			ret[p++] = pi(i, j);
		}
		py = coord[i].back();
	}
	for(int i=0; i<=mx; i++){
		coord[i].clear();
	}
	int q;
	scanf("%d",&q);
	while(q--){
		int t;
		scanf("%d",&t);
		printf("%d %d\n",ret[t-1].first, ret[t-1].second);
	}
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		solve();
	}
}