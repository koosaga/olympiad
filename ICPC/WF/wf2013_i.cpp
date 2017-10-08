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
typedef pair<lint, lint> pi;

int a, b, m, n;
int arr[505][505];
int h[505][505];

int main(){
	scanf("%d %d %d %d",&a,&b,&n,&m);
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			scanf("%d",&arr[i][j]);
		}
	}
	for(int i=0; i<n; i++){
		int tmp[505];
		memset(tmp, 0x3f, sizeof(tmp));
		tmp[m] = 0;
		for(int j=i; j<n; j++){
			for(int k=0; k<m; k++){
				tmp[k] = min(tmp[k], arr[j][k]);
			}
			stack<int> stk;
			for(int k=0; k<=m; k++){
				while(!stk.empty() && tmp[stk.top()] >= tmp[k]){
					int t = stk.top();
					stk.pop();
					int ntop = (stk.empty() ? -1 : stk.top());
					h[j-i+1][k-ntop-1] = max(h[j-i+1][k-ntop-1], tmp[t]);
				}
				stk.push(k);
			}
		}
	}
	for(int i=n; i; i--){
		for(int j=m; j; j--){
			h[i][j] = max(h[i][j], max(h[i+1][j], h[i][j+1]));
		}
	}
	lint ret = 0;
	for(int i=1; i<=a; i++){
		for(int j=1; j<=b; j++){
			if(i * j >= m * n) continue;
			lint up = 1ll * max(h[i][j], h[j][i]) * i * j - 1;
			ret = max(ret, 1ll * (max(h[i][j], h[j][i]) + up / (n * m - i * j)) * i * j);
		}
	}
	cout << ret;
}