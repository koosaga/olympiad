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
  
int n;
pi a[1505];
pi t[3005];
  
lint ccw(pi a, pi b){
	return 1ll * a.first * b.second - 1ll* b.first * a.second;
}
  
lint solve(int p){
	for(int i=0; i<n; i++){
		if(p == i) continue;
		if(p > i){
			t[i] = pi(a[i].first - a[p].first, a[i].second - a[p].second);
		}
		if(p < i){
			t[i-1] = pi(a[i].first - a[p].first, a[i].second - a[p].second);
		}
	}
	sort(t, t+n-1, [&](const pi &a, const pi &b){
		if(a.second == 0 && a.first > 0) return true;
		if(b.second == 0 && b.first > 0) return false;
		if(1ll * a.second * b.second < 0) return a.second > b.second;
		return ccw(a, b) > 0;
	});
	for(int i=0; i<n-1; i++){
		t[i+n-1] = t[i];
	}
	int e = 1;
	lint ret = 0;
	for(int i=0; i<n-1; i++){
		e = max(e, i+1);
		while(e < 2*n-2 && ccw(t[i], t[e]) > 0) e++;
		if(e - i - 1 > 1) ret += (e - i - 2) * (e - i - 1) / 2;
	}
	return ret;
}
  
int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first, &a[i].second);
	}
	lint ret = 0;
	for(int i=0; i<n; i++){
		ret += solve(i);
	}
	ret -= 1ll * n * (n-1) * (n-2) * (n-3) / 12;
	printf("%.6f",(6.0 * ret / (1ll * n * (n-1) * (n-2))) + 3);
}