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

int dp[505][505], dp2[505];
int a[505], sum[505][505], rmq[505][505], dist[505][505];
int n;

int getsum(int sx, int ex, int ey){
	return sum[ex][ey] - sum[sx-1][ey];
}

int cost(int s, int x, int e){
	int min1 = rmq[s][x];
	int min2 = rmq[x+1][e];
	if(min1 < min2) return e - s + 1 - getsum(s, x, min2 - 1);
	return e - s + 1 - getsum(x+1, e, min1 - 1);
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		for(int j=0; j<=500; j++){
			sum[i][j] = sum[i-1][j];
			if(j >= a[i]) sum[i][j]++;
		}
		rmq[i][i] = a[i];
	}
	for(int i=1; i<n; i++){
		for(int j=1; j+i<=n; j++){
			rmq[j][j+i] = min(rmq[j+1][j+i], rmq[j][j+i-1]);
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=i; j<=n; j++){
			dist[i][j] = 1;
			int arr[505] = {};
			for(int k=i; k<=j; k++){
				if(arr[a[k]]){
					dist[i][j] = 0;
					break;
				}
				arr[a[k]] = 1;
			}
		}
	}
	for(int i=1; i<n; i++){
		for(int j=1; j+i<=n; j++){
			dp[j][j+i] = 1e8;
			if(!dist[j][j+i]) continue;
			for(int k=j; k<j+i; k++){
				dp[j][j+i] = min(dp[j][j+i], dp[j][k] + dp[k+1][j+i] + cost(j, k, j+i));
			}
		}
	}
	for(int i=1; i<=n; i++){
		dp2[i] = 1e8;
		for(int j=0; j<i; j++){
			if(dist[j+1][i] && *max_element(a+j+1, a+i+1) == i-j) dp2[i] = min(dp2[i], dp2[j] + dp[j+1][i]);
		}
	}
	if(dp2[n] > 1e7) cout << "impossible";
	else cout << dp2[n];
}