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
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, a[20];
int l, r;

vector<int> st[1<<12];
vector<pi> ls;

void dfs(int pos, int z, int cst){
	if(pos == l){
		st[z].push_back(cst);
		return;
	}
	dfs(pos + 1, z|(1<<pos), cst + a[pos]);
	dfs(pos + 1, z|(1<<pos), cst - a[pos]);
	dfs(pos + 1, z, cst);
}

void dfs2(int pos, int z, int cst){
	if(pos == n){
		ls.push_back(pi(cst, z));
		return;
	}
	dfs2(pos + 1, z|(1<<pos), cst + a[pos]);
	dfs2(pos + 1, z|(1<<pos), cst - a[pos]);
	dfs2(pos + 1, z, cst);
}

bool ok[1<<20];

int main(){
	cin >> n;
	for(int i=0; i<n; i++) cin >> a[i];
	l = 3 * n / 5;
	r = n - l;
	dfs(0, 0, 0);
	dfs2(l, 0, 0);
	sort(ls.begin(), ls.end());
	for(int i=0; i<(1<<l); i++){
		sort(st[i].begin(), st[i].end());
		int p = 0;
		for(auto &j : st[i]){
			while(p < ls.size() && ls[p].first <= j){
				if(j == ls[p].first) ok[i|ls[p].second] = 1;
				p++;
			}
		}
	}
	for(int i=0; i<(1<<n); i++){
		if(ok[i]) printf("%d\n",i);
	}
	cout << count(ok + 1, ok + (1<<n), true);
}