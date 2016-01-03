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
const int S = 2500;

int n, arr[2505][2505];
pi a[250005];

int getsum(int sx, int ex, int sy, int ey){
	return arr[ex][ey] - arr[sx-1][ey] - arr[ex][sy-1] + arr[sx-1][sy-1];
}

int prec1[2505], prec2[2505], prec3[2505], prec4[2505];

pi contract1(int x, int y){
	return pi(max(x, prec2[y+1]), min(y, prec1[x-1])); 
}

pi contract2(int x, int y){
	return pi(min(x, prec4[y-1]), max(y, prec3[x+1]));
}

lint dp1[2505][2505], dp2[2505][2505];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first, &a[i].second);
		arr[a[i].first][a[i].second]++;
	}
	memset(prec1, 0x3f, sizeof(prec1));
	memset(prec4, 0x3f, sizeof(prec4));
	for(int i=0; i<n; i++){
		prec1[a[i].first] = min(prec1[a[i].first], a[i].second);
		prec2[a[i].second] = max(prec2[a[i].second], a[i].first);
		prec3[a[i].first] = max(prec3[a[i].first], a[i].second);
		prec4[a[i].second] = min(prec4[a[i].second], a[i].first);
	}
	for(int i=1; i<=S; i++){
		prec1[i] = min(prec1[i-1], prec1[i]);
		prec2[S+1-i] = max(prec2[S+1-i], prec2[S+2-i]);
		prec3[S+1-i] = max(prec3[S+1-i], prec3[S+2-i]);
		prec4[i] = min(prec4[i-1], prec4[i]);
	}
	for(int i=1; i<=S; i++){
		for(int j=1; j<=S; j++){
			arr[i][j] += arr[i-1][j] + arr[i][j-1] - arr[i-1][j-1];
		}
	}
	for(int i=S; i; i--){
		for(int j=1; j<=S; j++){
			pi nxt = contract1(i, j);
			dp1[i][j] = dp1[nxt.first][nxt.second] + getsum(i, S, 1, j);
		}
	}
	for(int i=1; i<=S; i++){
		for(int j=S; j; j--){
			pi nxt = contract2(i, j);
			dp2[i][j] = dp2[nxt.first][nxt.second] + getsum(1, i, j, S);
		}
	}
	for(int i=0; i<n; i++){
		printf("%lld\n",n - 3 + dp1[a[i].first][a[i].second] + dp2[a[i].first][a[i].second]);
	}
}