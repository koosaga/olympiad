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
const int mod = 97654321;

bool dp[400005];
vector<pi> v;

int main(){
	int n;
	scanf("%d",&n);
	while(n--){
		int a, l, c;
		scanf("%d %d %d",&a,&l,&c);
		while(c--){
			v.push_back(pi(l, a));
		}
	}
	dp[0] = 1;
	int sum = 0;
	sort(v.begin(), v.end());
	for(int i=0; i<v.size(); i++){
		sum += v[i].second;
		for(int j=min(v[i].first, sum); j>=v[i].second; j--){
			dp[j] |= dp[j - v[i].second];
		}
	}
	for(int i=sum; i>=0; i--){
		if(dp[i]){
			printf("%d",i);
			return 0;
		}
	}
}