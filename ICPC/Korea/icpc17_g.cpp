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
const int MAXN = 300005;
const int mod = 1e9 + 7;

int n, m;
int a[50005];
int L[55555], U[55555];

int main(){
	cin >> n >> m;
	a[0] = -20;
	a[2*n+2] = 50050;
	for(int i=1; i<=2*n+1; i++) scanf("%d",&a[i]);
	for(int i=0; i<=n; i++){
		for(int j=a[i*2]; j<a[i*2+2]; j++){
			L[j+20] = a[2*i+1];
		}
	}
	a[0] = -20;
	a[2*m+2] = 50050;
	for(int i=1; i<=2*m+1; i++) scanf("%d",&a[i]);
	for(int i=0; i<=m; i++){
		for(int j=a[i*2]; j<a[i*2+2]; j++){
			U[j+20] = a[2*i+1];
		}
	}
	lint cnt = 0, ans = 0;
	for(int i=0; i<50050; i++){
		if(L[i] >= U[i]) continue;
		int e = i;
		while(e < 50050 && L[e] < U[e]) e++;
		if(i != 0 && e != 50050){
			cnt++;
			for(int j=i; j<e; j++) ans += U[j] - L[j];
		}
		i = e-1;
	}
	cout << cnt << " " << ans << endl;
}
