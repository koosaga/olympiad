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
const double PI = acos(-1);

int n, r;
pi a[2005];

void solve(){
	int ret = 1;
	for(int i=0; i<n; i++){
		map<double, int> add;
		for(int j=0; j<n; j++){
			if(i == j) continue;
			double d = hypot(a[j].first - a[i].first, a[j].second - a[i].second);
			double ang = atan2(a[j].second - a[i].second, a[j].first - a[i].first);
			if(d > 2.0 * r + 1e-8) continue;
			double dx = acos((d - 1e-8) / (2.0 * r));
			double st = ang - dx, ed = ang + dx;
			while(st < 0){
				st += 2 * PI;
				ed += 2 * PI;
			}
			add[st]++;
			add[ed]--;
			if(ed < 2 * PI){
				add[st+2*PI]++;
				add[ed+2*PI]--;
			}
		}
		int sum = 0;
		for(auto &i : add){
			sum += i.second;
			ret = max(ret, sum + 1);
		}
	}
	printf("It is possible to cover %d points.\n",ret);
}
int main(){
	while(1){
		cin >> n >> r;
		if(n + r == 0) return 0;
		for(int i=0; i<n; i++){
			cin >> a[i].first >> a[i].second;
		}
		solve();
	}
}