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
int maxbit[8195];

bool f(int pos, int l, int r){
	if(pos == n + 1) return l == s[n];
	if(~dp[pos][l]) return dp[pos][l];
	int lsbl = l & -l;
	int lsbr = r & -r;
	int ans = 0;
	if(l == 0 || lsbl >= a[pos] || (lsbl == l && a[pos] >= lsbl)){
		if(lsbl == l){
			if(a[pos] > lsbl){
				if(f(pos + 1, a[pos], s[pos - 1])){
					dir[pos][l] = 1;
					ans = 1;
				}
			}
			else{
				if(f(pos + 1, l + a[pos], r)){
					dir[pos][l] = 1;
					ans = 1;
				}
			}
		}
		else{
			if(f(pos + 1, l + a[pos], r)){
				dir[pos][l] = 1;
				ans = 1;
			}
		}
	}
	if(r == 0 || lsbr >= a[pos]){
		int tr = r + a[pos];
		if((tr & -tr) == tr && maxbit[l] <= tr){
			if(f(pos + 1, s[pos], 0)){
				dir[pos][l] = 2;
				ans = 1;
			}
		}
		else{
			if(f(pos + 1, l, r + a[pos])){
				dir[pos][l] = 2;
				ans = 1;
			}
		}
	}
	return dp[pos][l] = ans;
}

void track(int pos, int l, int r){
//	printf("%d %d %d\n", pos, l, r);
	if(pos == n + 1) return;
	if(dir[pos][l] == 1){
		printf("l");
		int lsbl = l & -l;
		if(lsbl == l){
			if(a[pos] > lsbl){
				track(pos + 1, a[pos], s[pos - 1]);
			}
			else{
				track(pos + 1, l + a[pos], r);
			}
		}
		else{
			track(pos + 1, l + a[pos], r);
		}

	}
	else{
		printf("r");
		int tr = r + a[pos];
		if((tr & -tr) == tr && maxbit[l] <= tr){
			track(pos + 1, s[pos], 0);
		}
		else{
			track(pos + 1, l, r + a[pos]);
		}
	}
}

void solve(){
	if(s[n] != (s[n] & -s[n])){
		printf("no");
		return;
	}
	for(int i=0; i<n+2; i++) memset(dp[i], -1, sizeof(dp[i]));
	if(!f(1, 0, 0)){
		printf("no");
		return;
	}
	track(1, 0, 0);
}

int main(){
	int t;
	cin >> t;
	for(int i=0; i<=13; i++){
		for(int j=(1<<i); j<=8192; j++) maxbit[j] = (1<<i);
	}
	for(int i=0; i<t; i++){
		scanf("%d",&n);
		for(int i=1; i<=n; i++){
			scanf("%d",&a[i]);
			s[i] = a[i] + s[i-1];
		}
		solve();
		puts("");
	}
}
