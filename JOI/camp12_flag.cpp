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
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int k, n;
int x[1005], y[1005];
char s[1005][5];
int dp[1005][35];
int cnt[1005][35][3];
char mat[5] = "KOI";

int counter(int pos, int dep, int cs){
	if(pos == -1) return 0;
	if(~cnt[pos][dep][cs]) return cnt[pos][dep][cs];
	int ret = 0;
	for(int i=0; i<n; i++){
		if(((x[i] >> dep) == (x[pos] >> dep)) && ((y[i] >> dep) == (y[pos] >> dep))){
			if(mat[cs] != s[i][0]) ret++;
		}
	}
	return cnt[pos][dep][cs] = ret;
}

int locate(int bx, int by, int dep){
	for(int i=0; i<n; i++){
		if((x[i] >> dep) == bx && (y[i] >> dep) == by){
			return i;
		}
	}
	return -1;
}
int f(int pos, int dep){
	if(dep == 0) return 0;
	if(pos == -1) return 0;
	if(~dp[pos][dep]) return dp[pos][dep];
	int ret = 1e9;
	int p1 = locate((x[pos] >> dep) * 2, (y[pos] >> dep) * 2, dep-1);
	int p2 = locate((x[pos] >> dep) * 2, (y[pos] >> dep) * 2 + 1, dep-1);
	int p3 = locate((x[pos] >> dep) * 2 + 1, (y[pos] >> dep) * 2, dep-1);
	int p4 = locate((x[pos] >> dep) * 2 + 1, (y[pos] >> dep) * 2 + 1, dep-1);
	int buf[3] = {0, 1, 2};
	do{
		ret = min(ret, f(p1, dep-1) + counter(p2, dep-1, buf[0]) + counter(p3, dep-1, buf[1]) + counter(p4, dep-1, buf[2]));
		ret = min(ret, f(p2, dep-1) + counter(p1, dep-1, buf[0]) + counter(p3, dep-1, buf[1]) + counter(p4, dep-1, buf[2]));
		ret = min(ret, f(p3, dep-1) + counter(p1, dep-1, buf[0]) + counter(p2, dep-1, buf[1]) + counter(p4, dep-1, buf[2]));
		ret = min(ret, f(p4, dep-1) + counter(p1, dep-1, buf[0]) + counter(p2, dep-1, buf[1]) + counter(p3, dep-1, buf[2]));
	}while(next_permutation(buf, buf + 3));
	return dp[pos][dep] = ret;
}

int main(){
	memset(dp,-1,sizeof(dp));
	memset(cnt,-1,sizeof(cnt));
	scanf("%d %d",&k,&n);
	for(int i=0; i<n; i++){
		scanf("%d %d %s",&x[i],&y[i],s[i]);
		x[i]--;
		y[i]--;
	}
	printf("%d",f(0, k));
}