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

struct cow{
	int h, w, p;
	bool operator<(const cow &b)const{
		return p + w < b.p + b.w;
	}
}a[22];

int n, h;

int main(){
	cin >> n >> h;
	for(int i=0; i<n; i++){
		cin >> a[i].h >> a[i].w >> a[i].p;
	}
	sort(a, a+n);
	lint ret = -1;
	for(int i=1; i<(1<<n); i++){
		lint hsum = 0, wsum = 0, eval = 1e18;
		for(int j=0; j<n; j++){
			if((i >> j) & 1){
				hsum += a[j].h;
				eval = min(eval, a[j].p - wsum);
				wsum += a[j].w;
			}
		}
		if(hsum >= h) ret = max(ret, eval);
	}
	if(ret < 0) puts("Mark is too tall");
	else printf("%lld",ret);
}