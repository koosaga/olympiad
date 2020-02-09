#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 200005;

int n, l;
char str[MAXN];
int dp[4][MAXN];
int sum[4][MAXN];

int main(){
	scanf("%d %d %s",&n,&l,str + 1);
	for(int i=1; i<=n; i++){
		if(str[i] == 'J') sum[1][i]++;
		if(str[i] == 'O') sum[2][i]++;
		if(str[i] == 'I') sum[3][i]++;
		for(int j=0; j<4; j++){
			sum[j][i] += sum[j][i-1];
		}
	}
	for(int i=1; i<=3; i++){
		memset(dp[i], 0x3f, sizeof(dp[i]));
		int ptr = 0;
		int cur = 1e9;
		for(int j=1; j<=n; j++){
			while(ptr < j && sum[i][j] - sum[i][ptr] >= l){
				cur = min(cur, dp[i-1][ptr] - ptr);
				ptr++;
			}
			dp[i][j] = cur + j;
		}
	}
	int ans= *min_element(dp[3], dp[3] + n + 1) - 3 * l;
	if(ans > 1e7) ans = -1;
	cout << ans << endl;
}
