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
const int MAXN = 300005;
const int mod = 1e9 + 7;

vector<int> gph[MAXN];
vector<int> ord;
int n, m, dp[MAXN];

int main(){
	scanf("%d %d",&n,&m);
	ord.resize(n);
	iota(ord.begin(), ord.end(), 0);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	sort(ord.begin(), ord.end(), [&](const int &a, const int &b){
		return gph[a].size() > gph[b].size();
	});
	for(auto &i : ord){
		dp[i] = 0;
		for(auto &j : gph[i]){
			if(gph[j].size() > gph[i].size()) dp[i] = max(dp[i], dp[j]);
		}
		dp[i]++;
	}
	cout << *max_element(dp, dp + n + 1) << endl;
}
