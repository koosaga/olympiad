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
const int mod = 1e9 + 7;

lint ipow(int x, int p){
	lint ret = 1, piv = x;
	while(p){
		if(p & 1) ret *= piv;
		piv *= piv;
		ret %= mod;
		piv %= mod;
		p >>= 1;
	}
	return ret;
}

int n, s[505], e[505];
lint inv[1005], dp[505], sum[505], dp2[505][505];
vector<int> v;

int main(){
	cin >> n;
	for(int i=1; i<=n; i++){
		cin >> s[i] >> e[i];
		e[i]++;
		v.push_back(s[i]);
		v.push_back(e[i]);
	}
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	for(int i=1; i<=1000; i++){
		inv[i] = ipow(i, mod - 2);
	}
	dp[0] = 1;
	for(int i=1; i<v.size(); i++){
		int st = v[i-1], ed = v[i];
		vector<int> cnd;
		sum[0] = 1;
		for(int j=1; j<=n; j++){
			sum[j] = (sum[j-1] + dp[j]) % mod;
			if(s[j] <= st && ed <= e[j]){
				cnd.push_back(j);
			}
		}
		for(int i=1; i<=cnd.size() && i <= ed - st; i++){
			for(int j=i-1; j<cnd.size(); j++){
				if(i == 1){
					dp2[i][j] = sum[cnd[j] - 1] * (ed - st);
					if(j) dp2[i][j] += dp2[i][j-1];
					dp2[i][j] %= mod;
				}
				else{
					dp2[i][j] = (dp2[i-1][j-1] * inv[i] % mod) * (ed - st + 1 - i) + dp2[i][j-1];
					dp2[i][j] %= mod;
				}
			}
		}
		for(int i=1; i<=cnd.size() && i <= ed - st; i++){
			for(int j=i-1; j<cnd.size(); j++){
				int cnt = dp2[i][j] - (j ? dp2[i][j-1] : 0) + mod;
				cnt %= mod;
				dp[cnd[j]] += cnt;
				dp[cnd[j]] %= mod;
			}
		}
	}
	int ret= 0;
	for(int i=1; i<=n; i++){
		ret += dp[i];
		ret %= mod;
	}
	cout << ret;
}
