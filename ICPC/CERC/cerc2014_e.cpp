#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, a[1005], s[1005];
char dp[1005][8195];
char dir[1005][8195];

void getdp(){
	memset(dp[n+1], 0, sizeof(dp[n+1]));
	dp[n+1][s[n]] = 1;
	for(int i=n; i>=1; i--){
		for(int j=0; j<=s[i-1]; j++){
			int l = j, r = s[i-1] - j;
			int lsbl = (l & -l), lsbr = (r & -r);
			dp[i][j] = 0;
			if(l == 0 || lsbl >= a[i]){
				if(dp[i+1][l + a[i]]){
					dp[i][l] = 1;
					dir[i][l] = 1;
					continue;
				}
			}
			if(r == 0 || lsbr >= a[i]){
				int tr = r + a[i];
				if((tr & -tr) == tr && l < 2 * tr){
					dp[i][l] = dp[i+1][l+tr];
				}
				else{
					dp[i][l] = dp[i+1][l];
				}
				if(dp[i][l]) dir[i][l] = 2;
			}
		}
	}
}

void track(int pos, int l, int r){
	if(pos == n+1) return;
	if(dir[pos][l] == 1){
		putchar('l');
		track(pos+1, l+a[pos], r);
	}
	else{
		putchar('r');
		int tr = (r + a[pos]);
		if((tr & -tr) == tr && l < 2 * tr){
			track(pos + 1, l + tr, 0);
		}
		else{
			track(pos + 1, l, tr);
		}
	}
}

void solve(){
	getdp();
	if(!dp[1][0]){
		puts("no");
		return;
	}
	track(1, 0, 0);
	putchar('\n');
}

int main(){
	int t;
	cin >> t;
	while(t--){
		scanf("%d",&n);
		for(int i=1; i<=n; i++){
			scanf("%d",&a[i]);
			s[i] = a[i] + s[i-1];
		}
		if(s[n] != (s[n] & -s[n])){
			puts("no");
			continue;
		}
		solve();
	}
}