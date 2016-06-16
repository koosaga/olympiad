#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
#include <stdio.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int moe[200005], low[200005];
int n;
lint k;

lint solve(int n, double x){
	lint ret = 0;
	for(int i=1; i<=n; i++){
		ret += (int)floor(i * x);
	}
	return ret;
}

lint count(double x){
	lint ret = 0;
	for(int i=1; i<=n/2; i++){
		ret += solve(n/i, x) * 1ll * moe[i];
	}
	return ret;
}

int main(){
	cin >> n >> k;
	moe[1] = 1;
	for(int i=2; i<=n; i++){
		for(int j=i; j<=n; j+=i){
			if(!low[j]) low[j] = i;
		}
		int pv = -1;
		moe[i] = 1;
		for(int j=i; j!=1; j/=low[j]){
			if(pv == low[j]){
				moe[i] = 0;
				break;
			}
			pv = low[j];
			moe[i] *= -1;
		}
	}
	double s = 0, e = 1;
	for(int i=0; i<100; i++){
		double m = (s+e)/2;
		if(count(m) < k) s = m;
		else e = m;
	}
	for(int i=2; i<=n; i++){
		if(fabs(round(i * s) - i * s) < 1e-6){
			printf("%d %d",(int)round(i *s), i);
			return 0;
		}
	}
}