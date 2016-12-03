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
 
int n;
char buf[300005], str[600005];
int dp[600005];
 
vector<int> v[300005];
int prv[300005];

int lfind(int x){
	if(x == -1) return -1;
	if(prv[x] == x) return x;
	return prv[x] = lfind(prv[x]);
}
 
int solve(){
	int ret = 0;
	for(int i=0; i<n-1; i++){
		prv[i] = i;
		v[max(0, i-dp[i])].push_back(i);
	}
	set<int> s;
	for(int i=n-2; i>=0; i--){
		for(auto &j : v[i+1]){
			prv[j] = j-1;
		}
		int t = lfind(i + dp[i] / 2);
		if(t != -1) ret = max(ret, min(t - i, i + dp[i] - t));
	}
	return ret * 4;
}
 
int main(){
	int t;
	cin >> t;
	while(t--){
		cin >> buf;
		n = strlen(buf);
		for(int i=0; i<2*n+1; i++){
			if(i%2 == 1) str[i] = buf[i/2];
			else str[i] = '$';
		}
		int p = 0, cent = 0;
		for(int i=0; i<2*n+1; i++){
			dp[i] = 0;
			if(p >= i) dp[i] = min(p - i, dp[2 * cent - i]);
			while(i-dp[i]-1 >= 0 && i+dp[i]+1 < 2*n+1 && str[i-dp[i]-1] == str[i+dp[i]+1]){
				dp[i]++;
			}
			if(i + dp[i] > p){
				p = i + dp[i];
				cent = i;
			}
		}
		for(int i=0; i<n-1; i++){
			dp[i] = dp[2*i+2]/2;
		}
		cout << solve() << endl;
		for(int i=0; i<n; i++) v[i].clear();
	}
}