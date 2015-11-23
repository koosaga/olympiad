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

vector<int> coord;

int n, m, k;
pi a[2005];
int nxt[4005], vis[4005];
int dyn[2005], maxp[2005];
int dp[2005][2005][2];
int main(){
	scanf("%d %d %d",&n,&m,&k);
	k=n-k;
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
		coord.push_back(a[i].first);
		coord.push_back(a[i].second);
	}
	sort(coord.begin(), coord.end());
	memset(nxt, -1, sizeof(nxt));
	for(int i=0; i<n; i++){
		a[i].first = lower_bound(coord.begin(), coord.end(), a[i].first) - coord.begin();
		a[i].second = lower_bound(coord.begin(), coord.end(), a[i].second) - coord.begin();
		nxt[a[i].first] = a[i].second - 1;
	}
	memset(dyn, 0x3f, sizeof(dyn));
	dyn[0] = 0;
	for(int i=0; i<2*n; i++){
		if(!vis[i] && nxt[i] != -1){
			memset(maxp, 0x3f, sizeof(maxp));
			maxp[0] = 0;
			vector<int> v;
			if(nxt[i] == i){
				v.push_back(0);
				v.push_back(coord[i+1] - coord[i]);
				vis[i] = 1;
			}
			int p = i;
			while(p != -1 && !vis[p]){
				vis[p] = 1;
				v.push_back(coord[p+1] - coord[p]);
				p = nxt[p];
			}
			// if chain is long
			memset(dp[0],0x3f,sizeof(dp[0]));
			dp[0][0][0] = 0;
			for(int i=0; i<v.size(); i++){
				for(int j=0; j<v.size(); j++){
					if(j == 0) dp[i+1][j][0] = 0, dp[i+1][j][1] = 1e9;
					else{
						dp[i+1][j][1] = dp[i][j-1][1] + v[i];
						if(i) dp[i+1][j][1] = min(dp[i+1][j][1], dp[i][j-1][0] + v[i-1] + v[i]);
						dp[i+1][j][0] = min(dp[i][j][0], dp[i][j][1]);
					}
				}
			}
			int dyn2[2005];
			for(int i=0; i<=k; i++){
				dyn2[i] = 1e9;
				for(int j=0; j<v.size() && j<=i; j++){
					dyn2[i] = min(dyn2[i], dyn[i-j] + min(dp[v.size()][j][0], dp[v.size()][j][1]));
				}
			}
			memcpy(dyn, dyn2, sizeof(dyn2));
		}
	}
	printf("%d",m-dyn[k]);
}