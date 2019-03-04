#include <bits/stdc++.h>
using namespace std;
const int MAXN = 305;
const int mod = 1e9 + 7;
using lint = long long;
using pi = pair<int, int>;

int n, a[MAXN][MAXN];
bool vis[MAXN];
int seq[MAXN];
int bino[MAXN][MAXN];
int bsum[MAXN][MAXN];

pi dominated(int x){
	int chk[MAXN] = {};
	for(int i=0; i<n; i++){
		if(!vis[i] && x != i) chk[a[x][i]] = 1;
	}
	bool dap = count(chk, chk + MAXN, 1) <= 1;
	int yield = max_element(chk, chk + MAXN) - chk;
	return pi(dap, yield);
}

int solve(int *cnt){
	lint ret = 0;
	for(int i=1; i<=300; i++){
		for(int j=1; j<=cnt[i]; j++){
			lint poss = bino[cnt[i]][j];
			for(int k=1; k<i; k++){
				poss *= bsum[cnt[k]][j-1];
				poss %= mod;
			}
			for(int k=i+1; k<=300; k++){
				poss *= bsum[cnt[k]][j];
				poss %= mod;
			}
			poss *= j;
			ret += poss;
		}
	}
	return ret % mod;
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=0; i<=n; i++){
		bino[i][0] = 1;
		bsum[i][0] = 1;
		for(int j=1; j<=n; j++){
			bino[i][j] = (bino[i-1][j] + bino[i-1][j-1]) % mod;
			bsum[i][j] = (bsum[i][j-1] + bino[i][j]) % mod;
		}
	}
	int sz = 0;
	while(sz < n-1){
		for(int i=0; i<n; i++){
			if(!vis[i]){
				pi val = dominated(i);
				if(val.first == 0) continue;
				seq[sz++] = val.second;
				vis[i] = 1;
				break;
			}
		}
	}
	lint ret = 0;
	for(int i=0; i<n; i++){
		int cnt[MAXN] = {};
		for(int j=0; j<i; j++) cnt[seq[j]]++;
		lint dap = solve(cnt);
		lint pwr = 1;
		for(int j=0; j<i; j++) pwr = pwr * 2 % mod;
		ret += dap + pwr;
	}
	cout << ret % mod << endl;
}
