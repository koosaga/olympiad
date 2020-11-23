#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1000005;

int n, a[MAXN];
int dp[MAXN][2][2];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d",&a[i]);
		if(a[i] > 2){
			puts("NO");
			return 0;
		}
	}
	if(a[0] > 1 || a[n-1] > 1){
		puts("NO");
		return 0;
	}
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			if((i ^ j) == a[0]){
				dp[1][i][j] = 1;
			}
		}
	}
	for(int i=1; i<n-1; i++){
		for(int j=0; j<2; j++){
			for(int k=0; k<2; k++){
				if(!dp[i][j][k]) continue;
				for(int l=0; l<2; l++){
					for(int m=0; m<2; m++){
						int indeg_first = j + (1 - l);
						int indeg_second = k + (1 - m);
						if(abs(indeg_first - indeg_second) == a[i]){
							dp[i+1][l][m] = 1;
						}
					}
				}
			}
		}
	}
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			if((i ^ j) == a[n-1] && dp[n-1][i][j]){
				puts("YES");
				return 0;
			}
		}
	}
	puts("NO");
}
