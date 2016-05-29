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
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n;
pi a[100005];
int ret[100005];
int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		int s, t;
		scanf("%d %d",&s, &t);
		a[i] = pi(t+s, t-s);
	}
	sort(a, a+n);
	map<int, int> mp;
	int pt = 0;
	for(int i=0; i<n; i++){
		auto tmp = mp.upper_bound(a[i].second);
		if(tmp == mp.begin()){
			mp[a[i].second] = ++pt;
			ret[i] = pt;
		}
		else{
			tmp--;
			int pnt = tmp->second;
			mp.erase(tmp);
			mp[a[i].second] = pnt;
			ret[i] = pnt;
		}
	}
	printf("%d\n",pt);
	for(int i=0; i<n; i++){
		lint s = (1ll * a[i].first - 1ll * a[i].second) / 2;
		lint t = a[i].first - s;
		printf("%lld %lld %d\n",s, t, ret[i]);
	}
}