#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 5005;

int n, pos[MAXN], dp[MAXN];
int sum[MAXN][MAXN];

int cost(int j, int i){
	return sum[i][i] - sum[i][j] - sum[j][i] + sum[j][j];
}

int main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		int x; cin >> x;
		pos[x] = i;
	}
	int ret = 0;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j < i; j++){
			if(pos[j] > pos[i]) ret++;
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			if(i < j && pos[i] > pos[j]) sum[i][j]--;
			if(pos[i] < pos[j] && i < j) sum[i][j]++;
			sum[i][j] += sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
		}
	}
	for(int i = 1; i <= n; i++){
		dp[i] = 1e9;
		for(int j = 0; j < i; j++){
			dp[i] = min(dp[i], dp[j] + cost(j, i));
		}
	}
	cout << dp[n] + ret<< endl;
}
