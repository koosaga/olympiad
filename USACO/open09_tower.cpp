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

int n, a[100005], dp[100005], res[100005];
vector<pi> v;

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d",&a[i]);
	}
	for(int i=n-1; i>=0; i--){
		a[i] += a[i+1];
	}
	v.push_back(pi(0, n));
	for(int i=n-1; i>=0; i--){
		int s = 0, e = (int)v.size() - 1;
		while(s != e){
			int m = (s+e+1)/2;
			if(a[i] >= v[m].first) s = m;
			else e = m-1;
		}
		dp[i] = a[i] - a[v[s].second];
		res[i] = res[v[s].second] + 1;
		while(!v.empty() && v.back().first >= dp[i] + a[i]){
			v.pop_back();
		}
		v.push_back(pi(dp[i] + a[i], i));
	}
	printf("%d",res[0]);
}