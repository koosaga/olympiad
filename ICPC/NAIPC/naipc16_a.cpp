#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

int m, n, k;
int s[105], e[105], x[105], y[105];
int need[1<<20], popcnt[1<<20];
int dp[1<<20][21];

int main(){
	for(int i=1; i<(1<<20); i++) popcnt[i] = popcnt[i - (i & -i)] + 1;
	cin >> m >> n >> k;
	int cst = 0;
	for(int i=0; i<m; i++){
		cin >> s[i] >> x[i] >> e[i] >> y[i];
		s[i]--; e[i]--;
		if(s[i] > e[i]){
			swap(s[i], e[i]);
			swap(x[i], y[i]);
		}
		cst += min(x[i], y[i]);
	}
	for(int i=0; i<(1<<(n/2)); i++){
		for(int j=0; j<m; j++){
			if(s[j] < n/2 && e[j] >= n/2 && (i >> s[j]) % 2 == 0){
				need[i] |= (1 << (e[j] - n/2));
			}
		}
	}
	vector<pi> v1, v2;
	for(int i=0; i<(1<<(n/2)); i++){
		bool ok = 1;
		int cost = 0;
		for(int j=0; j<m; j++){
			if(e[j] < n/2){
				bool c1 = (i >> s[j]) & 1;
				bool c2 = (i >> e[j]) & 1;
				if(!c1 && !c2) ok = 0;
				else if(c1 && !c2) cost += x[j] - min(x[j], y[j]);
				else if(!c1 && c2) cost += y[j] - min(x[j], y[j]);
			}
			else if(s[j] < n/2 && e[j] >= n/2 && (i >> s[j]) % 2 == 0){
				cost += y[j] - min(x[j], y[j]);
			}
		}
		if(ok) v1.push_back(pi(i, cost));
	}
	for(int i=0; i<(1<<(n-n/2)); i++){
		bool ok = 1;
		int cost = 0;
		for(int j=0; j<m; j++){
			if(s[j] >= n/2){
				bool c1 = (i >> (s[j] - n/2)) & 1;
				bool c2 = (i >> (e[j] - n/2)) & 1;
				if(!c1 && !c2) ok = 0;
				else if(c1 && !c2) cost += x[j] - min(x[j], y[j]);
				else if(!c1 && c2) cost += y[j] - min(x[j], y[j]);
			}
			else if(s[j] < n/2 && e[j] >= n/2 && (i >> (e[j] - n/2)) % 2 == 0){
				cost += x[j] - min(x[j], y[j]);
			}
		}
		if(ok) v2.push_back(pi(i, cost));
	}
	int minv = 1e9 + 100;
	memset(dp, 0x3f, sizeof(dp));
	int v = n-n/2;
	for(auto &i : v2){
		for(int j=popcnt[i.first]; j<=v; j++){
			dp[i.first][j] = i.second;
		}
	}
	for(int i=(1<<v)-1; i>=0; i--){
		for(int j=0; j<=v; j++){
			for(int k=0; k<v; k++){
				if((i >> k) % 2 == 0) dp[i][j] = min(dp[i][j], dp[i | (1<<k)][j]);
			}
		}
	}
	for(auto &i : v1){
		if(popcnt[i.first] > k) continue;
		int l = min(v, k - popcnt[i.first]);
		minv = min(minv, i.second + dp[need[i.first]][l]);
	}
	if(minv > 1e9 + 10) cout << -1;
	else cout << minv + cst;
}

