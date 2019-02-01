#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int l[3], a[3][3005];
int dp1[3005][3005], dp2[3005][3005];
int opt[2][3005];

int main(){
	for(int i=0; i<3; i++){
		scanf("%d",&l[i]);
		for(int j=1; j<=l[i]; j++){
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=1; i<=l[0]; i++){
		for(int j=1; j<=l[1]; j++){
			dp1[i][j] = max(dp1[i-1][j], dp1[i][j-1]);
			if(a[0][i] == a[1][j]){
				dp1[i][j] = max(dp1[i][j], dp1[i-1][j-1] + 1);
			}
		}
	}
	for(int i=l[0]; i; i--){
		for(int j=l[1]; j; j--){
			dp2[i][j] = max(dp2[i][j+1], dp2[i+1][j]);
			if(a[0][i] == a[1][j]){
				dp2[i][j] = max(dp2[i][j], dp2[i+1][j+1] + 1);
			}
		}
	}
	for(int i=0; i<2; i++){
		for(int j=1; j<=l[i]; j++){
			int pos = j-1;
			for(int k=1; k<=l[2]; k++){
				pos++;
				while(pos <= l[i] && a[i][pos] != a[2][k]) pos++;
			}
			if(pos > l[i]) pos = 1e9;
			opt[i][j] = pos + 1;
		}
	}
	int ret = -1;
	for(int i=0; i<l[0]; i++){
		for(int j=0; j<l[1]; j++){
			if(opt[0][i+1] > 1e8 || opt[1][j+1] > 1e8) continue;
			ret = max(ret,dp1[i][j] + l[2] + dp2[opt[0][i+1]][opt[1][j+1]]);
		}
	}
	cout << ret;
}
