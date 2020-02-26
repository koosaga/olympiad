#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 100005;

int chk[4][MAXN];

int main(){
	int tc; scanf("%d",&tc);
	while(tc--){
		int n, k;
		scanf("%d %d",&n,&k);
		for(int i=0; i<k;i++){
			int x; scanf("%d",&x);
			for(int j=0; j<x; j++){
				int y; scanf("%d",&y);
				chk[i][y] = 1;
			}
		}
		int card[16] = {};
		int dp[16];
		for(int i=1; i<16; i++){
			for(int j=1; j<=n; j++){
				bool good = 0;
				for(int k=0; k<4; k++){
					if((i >> k) % 2 && chk[k][j] == 1) good = 1;
				}
				card[i] += good;
			}
		}
		for(int i=1; i<16; i++){
			dp[i] = 1e9;
			for(int j=i; j; j=(j-1)&i){
				dp[i] = min(dp[i], max(dp[i^j], card[j]));
			}
		}
		printf("%d\n", dp[15]);
		for(int i=0; i<4; i++){
			for(int j=0; j<=n; j++) chk[i][j] = 0;
		}
	}
}
