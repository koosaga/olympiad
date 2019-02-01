#include <bits/stdc++.h>
using namespace std;
const int MAXN = 4105;
const int mod = 1e9 + 433;
const int bse = 65537;
using pi = pair<int, int>;
using lint = long long;

int n, m, k;
lint pwr[MAXN], dap[MAXN];
char str[MAXN][MAXN];

int cnt(int x, int y){
	int ret = 0;
	for(int i=0; i<m; i++){
		if(str[x][i] != str[y][i]) ret++;
	}
	return ret;
}

int main(){
	scanf("%d %d %d",&n,&m,&k);
	for(int i=0; i<n; i++) scanf("%s", str[i]);
	pwr[0] = 1;
	for(int i=0; i<n; i++) pwr[i+1] = pwr[i] * bse % mod;
	for(int i=0; i<m; i++){
		lint ans[256] = {};
		lint tot = 0;
		for(int j=0; j<n; j++){
			ans[str[j][i]] += pwr[j + 1];
			tot += pwr[j + 1];
		}
		for(int j=0; j<n; j++){
			dap[j] += tot - ans[str[j][i]];
			dap[j] %= mod;
		}
	}
	for(int i=0; i<n; i++){
		lint ret = 0;
		for(int j=0; j<n; j++){
			if(i != j) ret += pwr[j + 1] * k % mod;
		}
		ret %= mod;
		if(ret == dap[i]){
			bool fail = 0;
			for(int j=0; j<n; j++){
				if(i != j && cnt(i, j) != k){
					fail = 1;
					break;
				}
			}
			if(!fail){
				cout << i + 1 << endl;
				return 0;
			}
		}
	}
}
