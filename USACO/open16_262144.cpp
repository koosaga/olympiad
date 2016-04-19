#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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

int n;
lint a[300005];
bool ok[60][300005];

int main(){
	freopen("262144.in","r",stdin);
	freopen("262144.out","w",stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		int t;
		scanf("%d",&t);
		a[i] = a[i-1] + (1ll<<t);
		if(t == 0) ok[0][i] = 1;
	}
	for(int i=1; i<60; i++){
		int pnt = 0, qnt = 0;
		for(int j=1; j<=n; j++){
			while(pnt < n && a[pnt] - a[j-1] < (1ll<<i)){
				pnt++;
			}
			while(qnt < n && a[qnt] - a[j-1] < (1ll<<(i-1))){
				qnt++;
			}
			if(a[pnt] - a[j-1] == (1ll<<i)){
				if(pnt == j) ok[i][j] = 1;
				else ok[i][j] = ok[i-1][j] & ok[i-1][qnt+1];
			}
		}
	}
	for(int i=59; i>=0; i--){
		for(int j=1; j<=n; j++){
			if(ok[i][j]){
				printf("%d",i);
				return 0;
			}
		}
	}
}