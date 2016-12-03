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

int n;
pi a[100005];

int g(int x, int y){
	return y ? g(y, x%y) : x;
}

void solve(){
	scanf("%d",&n);
	int cb = 0, cw = 0;
	for(int i=0; i<n; i++){
		char buf[3];
		scanf("%d %s",&a[i].first, buf);
		a[i].second = buf[0];
		if(buf[0] == 'B') cb += a[i].first;
		else cw += a[i].first;
	}
	if(cb == 0 || cw == 0){
		printf("%d\n",max(cb, cw));
		return;
	}
	int gcd = g(cb, cw);
	cb /= gcd, cw /= gcd;
	int currb = 0, currw = 0;
	int ret = 0;
	for(int i=0; i<n; i++){
		if(a[i].second == 'B'){
			lint tmp = 1ll * cb * currw - 1ll * cw * currb;
			if(tmp % cw == 0){
				tmp /= cw;
				if(tmp <= a[i].first && tmp > 0){
					currb = a[i].first - tmp;
					currw = 0;
					ret++;
				}
				else{
					currb += a[i].first;
				}
			}
			else{
				currb += a[i].first;
			}
		}
		if(a[i].second == 'W'){
			lint tmp = 1ll * currb * cw - 1ll * currw * cb;
			if(tmp % cb == 0){
				tmp /= cb;
				if(tmp <= a[i].first && tmp > 0){
					currw = a[i].first - tmp;
					currb = 0;
					ret++;
				}
				else{
					currw += a[i].first;
				}
			}
			else{
				currw += a[i].first;
			}
		}
	}
	printf("%d\n",ret);
}

int main(){
	int t;
	cin >> t;
	while(t--) solve();
}