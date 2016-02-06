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

int n, m;
char str[205][205];
int psum[205][205];
int pt[205][205];

int main(){
	freopen("fortmoo.in","r",stdin);
	freopen("fortmoo.out","w",stdout);
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		scanf("%s",str[i] + 1);
		for(int j=1; j<=m; j++){
			psum[i][j] = psum[i][j-1] + (str[i][j] == 'X');
		}
	}
	int ret = 0;
	for(int j=1; j<=m; j++){
		for(int k=j; k<=m; k++){
			pt[j][k] = 1;
			while(pt[j][k] <= n && psum[pt[j][k]][k-1] != psum[pt[j][k]][j]){
				pt[j][k]++;
			}
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			for(int k=j; k<=m; k++){
				if(pt[j][k] <= i && (str[i][k] == 'X' || str[i][j] == 'X')){
					pt[j][k] = i+1;
					while(pt[j][k] <= n && psum[pt[j][k]][k-1] != psum[pt[j][k]][j]){
						pt[j][k]++;
					}
				}
			}
		}
		for(int j=1; j<=m; j++){
			for(int k=j; k<=m; k++){
				if(psum[i][k] - psum[i][j-1] == 0 && pt[j][k] <= i){
					ret = max(ret, (k - j + 1) * (i - pt[j][k] + 1));
				}
			}
		}
	}
	printf("%d",ret);
}