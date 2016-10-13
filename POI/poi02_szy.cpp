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

vector<pi> v1, v2;
int n, a[44];

void dfs(int bit, int sum, int dep){
	if(dep == n/2){
		v1.push_back(pi(sum, bit));
		return;
	}
	dfs(bit, sum, dep + 1);
	dfs(bit|(1<<dep), sum + a[dep], dep + 1);
}

void dfs2(int bit, int sum, int dep){
	if(dep == n){
		v2.push_back(pi(sum, bit));
		return;
	}
	dfs2(bit, sum, dep + 1);
	dfs2(bit|(1<<(dep - n/2)), sum + a[dep], dep + 1);
}
int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d",&a[i]);
	}
	dfs(0,0,0);
	dfs2(0,0,n/2);
	int k;
	scanf("%d",&k);
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	for(auto &i : v1){
		auto t = lower_bound(v2.begin(), v2.end(), pi(k - i.first, -1));
		if(t != v2.end() && t->first == k - i.first){
			for(int j=0; j<n/2; j++){
				printf("%d",(i.second >> j) & 1);
			}
			int tmp = t->second;
			for(int j=n/2; j<n; j++){
				printf("%d",tmp & 1);
				tmp >>= 1;
			}
			return 0;
		}
	}
}