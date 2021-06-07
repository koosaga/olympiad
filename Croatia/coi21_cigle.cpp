// shirley smokes weed
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 5005;

int n, a[MAXN];
int dp[MAXN][MAXN];

int main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		a[i] += a[i-1];
	}
	for(int i = 1; i < n; i++){
		vector<int> pos;
		vector<int> pmax(n + 1);
		for(int j = 0; j <= n; j++) pmax[j] = dp[j][i];
		for(int j = 1; j <= n; j++) pmax[j] = max(pmax[j], pmax[j - 1]);
		int ptr = i;
		for(int k = i+1; k <= n; k++){
			int cur_thres = 2 * a[i] - a[k];
			dp[i][k] = max(dp[i][k - 1], pmax[ptr - 1] + sz(pos));

			while(ptr > 1 && a[ptr] > cur_thres){
				ptr--;
				dp[i][k] = max(dp[i][k], dp[ptr][i] + sz(pos));
			}
			if(a[ptr] == cur_thres){
				pos.push_back(ptr);
			}
		}
	}
	int ret = 0;
	for(int i = 1; i <= n; i++) ret = max(ret, dp[i-1][n]);
	cout << ret << endl;
}

