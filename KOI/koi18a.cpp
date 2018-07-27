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
const int MAXN = 300005;
const int mod = 1e9 + 7;

vector<int> v[MAXN];

lint solve(vector<int> &v){
	if(v.size() <= 1) return 0;
	lint ret = 0;
	for(int i=0; i<v.size(); i++){
		int ans = 1e9;
		if(i + 1 < v.size()) ans = min(ans, v[i+1] - v[i]);
		if(i > 0) ans = min(ans, v[i] - v[i-1]);
		ret += ans;
	}
	return ret;
}

int main(){
	int n;
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		v[y].push_back(x);
	}
	lint ans = 0;
	for(int i=1; i<=n;i++){
		sort(v[i].begin(), v[i].end());
		ans += solve(v[i]);
	}
	cout << ans << endl;
}
