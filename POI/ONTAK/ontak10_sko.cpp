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
int mod;

int n, dfn[1500005], rev[1500005], piv;
vector<int> gph[1500005];

void dfs(int x){
	dfn[x] = ++piv;
	rev[dfn[x]] = x;
	for(auto &i : gph[x]){
		gph[i].erase(find(gph[i].begin(), gph[i].end(), x));
		dfs(i);
	}
}

int dp1[1500005][2];
lint dp2[1500005][2];
vector<lint> pfx, sfx;

int main(){
	cin >> n;
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	cin >> mod;
	dfs(1);
	for(int i=n; i; i--){
		int p = rev[i];
		int pmax = 0;
		dp2[p][1] = 1;
		pfx.clear(), sfx.clear();
		pfx.resize(gph[p].size());
		sfx.resize(gph[p].size());
		for(auto &j : gph[p]){
			dp1[p][1] += dp1[j][0];
			dp2[p][1] *= dp2[j][0];
			dp2[p][1] %= mod;
			dp1[p][0] += dp1[j][0];
			pmax = max(pmax, dp1[j][1] - dp1[j][0] + 1);
		}
		dp1[p][0] += pmax;
		lint rp1 = 1, rp2 = 1;
		for(int j=0; j<gph[p].size(); j++){
			rp1 *= dp2[gph[p][j]][0];
			rp2 *= dp2[gph[p][gph[p].size()-1-j]][0];
			rp1 %= mod;
			rp2 %= mod;
			pfx[j] = rp1;
			sfx[gph[p].size()-1-j] = rp2;
		}
		if(pmax == 0){
			dp2[p][0] = rp1;
		}
		for(int j=0; j<gph[p].size(); j++){
			int k = gph[p][j];
			if(dp1[k][1] - dp1[k][0] + 1 == pmax){
				dp2[p][0] += (1ll * (j ? pfx[j-1] : 1) * (j + 1 < gph[p].size() ? sfx[j+1] : 1) % mod) * dp2[k][1] % mod;
				dp2[p][0] %= mod;
			}
		}
	}
	cout << dp1[1][0] << endl << dp2[1][0] % mod;
}