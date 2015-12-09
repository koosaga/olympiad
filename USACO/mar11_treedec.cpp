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
vector<int> graph[100005];
int c[100005], t[100005];
lint ret;

lint dfs(int x, int p){
	lint sum = 0;
	for(auto &i : graph[x]){
		sum += dfs(i, x);
		t[x] = min(t[x], t[i]);
	}
	ret += 1ll * max(0ll, c[x] - sum) * t[x];
	return max(1ll * c[x], sum);
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		int p;
		scanf("%d %d %d",&p,&c[i],&t[i]);
		if(i != 1) graph[p].push_back(i);
	}
	dfs(1, 0);
	cout << ret;
}