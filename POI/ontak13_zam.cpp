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

int a[305][305];
int u[305][305], l[305][305], ul[305][305], ur[305][305], dl[305][305], dr[305][305];
int n, m, k;

int main(){
	scanf("%d %d %d",&n,&m,&k);
	for(int j=0; j<=n+1; j++){
		fill(u[j], u[j] + m + 2, -2e9);
		fill(l[j], l[j] + m + 2, -2e9);
		fill(ul[j], ul[j] + m + 2, -2e9);
		fill(ur[j], ur[j] + m + 2, -2e9);
		fill(dl[j], dl[j] + m + 2, -2e9);
		fill(dr[j], dr[j] + m + 2, -2e9);
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			scanf("%d",&a[i][j]);
			a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=i; j<=n; j++){
			int tmp[305] = {};
			for(int k=1; k<=m; k++){
				tmp[k] = a[j][k] - a[i-1][k] - a[j][k-1] + a[i-1][k-1];
			}
			int cur = 0, ret = -2e9;
			for(int k=1; k<=m; k++){
				ret = max(ret, tmp[k]);
				cur += tmp[k];
				if(cur < 0) cur = 0;
				if(ret >= 0){
					ret = max(ret, cur);
				}
				ul[j][k] = max(ul[j][k], ret);
				dl[i][k] = max(dl[i][k], ret);
			}
			l[i][j] = ret;
			cur = 0, ret = -2e9;
			for(int k=m; k; k--){
				ret = max(ret, tmp[k]);
				cur += tmp[k];
				if(cur < 0) cur = 0;
				if(ret >= 0){
					ret = max(ret, cur);
				}
				ur[j][k] = max(ur[j][k], ret);
				dr[i][k] = max(dr[i][k], ret);
			}
		}
	}
	for(int i=1; i<=m; i++){
		for(int j=i; j<=m; j++){
			int tmp[305] = {};
			for(int k=1; k<=n; k++){
				tmp[k] = a[k][j] - a[k][i-1] - a[k-1][j] + a[k-1][i-1];
			}
			int cur = 0, ret = -2e9;
			for(int k=1; k<=n; k++){
				ret = max(ret, tmp[k]);
				cur += tmp[k];
				if(cur < 0) cur = 0;
				if(ret >= 0){
					ret = max(ret, cur);
				}
				ul[k][j] = max(ul[k][j], ret);
				ur[k][i] = max(ur[k][i], ret);
			}
			u[i][j] = ret;
			cur = 0, ret = -2e9;
			for(int k=n; k; k--){
				ret = max(ret, tmp[k]);
				cur += tmp[k];
				if(cur < 0) cur = 0;
				if(ret >= 0){
					ret = max(ret, cur);
				}
				dl[k][j] = max(dl[k][j], ret);
				dr[k][i] = max(dr[k][i], ret);
			}
			u[i][j] = ret;
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			ul[i][j] = max(ul[i-1][j], max(ul[i][j], ul[i][j-1]));
		}
		for(int j=m; j; j--){
			ur[i][j] = max(ur[i-1][j], max(ur[i][j], ur[i][j+1]));
		}
	}
	for(int i=n; i; i--){
		for(int j=1; j<=m; j++){
			dl[i][j] = max(dl[i+1][j], max(dl[i][j], dl[i][j-1]));
		}
		for(int j=m; j; j--){
			dr[i][j] = max(dr[i+1][j], max(dr[i][j], dr[i][j+1]));
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j+i<=n; j++){
			l[j][i+j] = max(l[j][i+j], max(l[j+1][i+j], l[j][i+j-1]));
		}
	}
	for(int i=1; i<=m; i++){
		for(int j=1; j+i<=m; j++){
			u[j][i+j] = max(u[j][i+j], max(u[j+1][i+j], u[j][i+j-1]));
		}
	}
	if(k == 1){
		printf("%d",ul[n][m]);
		return 0;
	}
	if(k == 2){
		int ret = -2e9;
		for(int i=1; i<n; i++){
			ret = max(ret, l[1][i] + l[i+1][n]);
		}
		for(int i=1; i<m; i++){
			ret = max(ret, u[1][i] + u[i+1][m]);
		}
		printf("%d",ret);
		return 0;
	}
	int ret = -2e9;
	for(int i=1; i<n; i++){
		for(int j=i+1; j<n; j++){
			ret = max(ret,l[1][i] + l[i+1][j] + l[j+1][n]);
		}
	}
	for(int i=1; i<m; i++){
		for(int j=i+1; j<m; j++){
			ret = max(ret,u[1][i] + u[i+1][j] + u[j+1][m]);
		}
	}
	for(int i=1; i<n; i++){
		for(int j=1; j<m; j++){
			ret = max(ret, ul[i][j] + ur[i][j+1] + l[i+1][n]);
			ret = max(ret, l[1][i] + dl[i+1][j] + dr[i+1][j+1]);
			ret = max(ret, u[1][j] + ur[i][j+1] + dr[i+1][j+1]);
			ret = max(ret, u[j+1][n] + ul[i][j] + dl[i+1][j]);
		}
	}
	printf("%d\n",ret);
}