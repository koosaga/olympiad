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

int n, a[1000005];

void solve(){
	cin >> n;
	for(int i=0; i<n; i++) scanf("%d",&a[i]);
	sort(a, a+n);
	for(int i=0; i<n; ){
		int e = i;
		while(e < n && a[e] == a[i]) e++;
		if(n%2 == 0 && (e-i) > n/2){
			puts("NIE");
			return;
		}
		if(n%2 == 1 && (e-i) > n/2 && e != n && i != 0){
			puts("NIE");
			return;
		}
		if(n%2 == 1 && (e-i) > n/2+1){
			puts("NIE");
			return;
		}
		i = e;
	}
	puts("TAK");
}

int main(){
	int t;
	cin >> t;
	while(t--) solve();
}

