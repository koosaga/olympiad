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

char str[155][155][155];
bool tab[155][155][155];
int p, q, r;

int height[155][155];

int solve2(int n, int m){
	int ret = 0;
	for(int i=1; i<=n; i++){
		int h[151] = {};
		for(int j=1; j<=m; j++){
			int minp = 1e9;
			for(int k=i; k; k--){
				minp = min(minp, height[k][j]);
				if(h[j] + 1 <= minp){
					h[j]++;
				}
				else break;
			}
		}
		stack<int> stk;
		for(int j=1; j<=m; j++){
			while(!stk.empty() && h[stk.top()] >= h[j]){
				int bk = stk.top();
				stk.pop();
				ret = max(ret, (j - 1 - (stk.empty() ? 0 : stk.top())) * h[bk]);
			}
			stk.push(j);
		}
		while(!stk.empty()){
			int bk = stk.top();
			stk.pop();
			ret = max(ret, (m - (stk.empty() ? 0 : stk.top())) * h[bk]);
		}
	}
	return ret;
}

int solve(int p, int q, int r){
	memset(height,0,sizeof(height));
	int ret = 0;
	for(int i=1; i<=p; i++){
		for(int j=1; j<=q; j++){
			for(int k=1; k<=r; k++){
				height[j][k] = (tab[i][j][k] ? height[j][k] + 1 : 0);
			}
		}
		ret = max(ret, solve2(q, r) * 4);
	}
	return ret;
}

int main(){
	scanf("%d %d %d",&q,&p,&r);
	for(int i=1; i<=p; i++){
		for(int j=1; j<=q; j++){
			scanf("%s",str[i][j] + 1);
		}
	}
	for(int i=1; i<=p; i++){
		for(int j=1; j<=q; j++){
			for(int k=1; k<=r; k++){
				tab[i][j][k] = (str[i][j][k] == 'N');
			}
		}
	}
	int ret = solve(p, q, r);
	memset(tab, 0, sizeof(tab));
	for(int i=1; i<=q; i++){
		for(int j=1; j<=r; j++){
			for(int k=1; k<=p; k++){
				tab[i][j][k] = (str[k][i][j] == 'N');
			}
		}
	}
	ret = max(ret, solve(q, r, p));
	memset(tab, 0, sizeof(tab));
	for(int i=1; i<=r; i++){
		for(int j=1; j<=p; j++){
			for(int k=1; k<=q; k++){
				tab[i][j][k] = (str[j][k][i] == 'N');
			}
		}
	}
	ret = max(ret, solve(r, p, q));
	printf("%d",ret);
}
