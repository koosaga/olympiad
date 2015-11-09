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
const int mod = 97654321;

int adj[52][52];

int get(char x){
	if(x >= 'a' && x <= 'z') return x - 'a';
	return x - 'A' + 26;
}

int dp[260][260][53];

int f(int a, int b, int t){
	if(a < 0 || b < 0) return 0;
	if(a + b == 0) return 1;
	if(~dp[a][b][t]) return dp[a][b][t];
	int ret = 0;
	for(int i=0; i<52; i++){
		if(adj[t][i]){
			if(i >= 26) ret += f(a-1, b, i);
			else ret += f(a, b-1, i);
		}
		ret %= mod;
	}
	return dp[a][b][t] = ret;
}

int main(){
	memset(dp,-1,sizeof(dp));
	int u, l, q;
	scanf("%d %d %d",&u,&l,&q);
	while(q--){
		char buf[5];
		scanf("%s",buf);
		adj[get(buf[0])][get(buf[1])] = 1;
	}
	for(int i=0; i<52; i++) adj[52][i] = 1;
	printf("%d",f(u, l, 52));
}