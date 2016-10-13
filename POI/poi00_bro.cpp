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

int n, a[10005], d[20005], sum;

int main(){
	cin >> n;
	for(int i=1; i<=n; i++){
		cin >> a[i] >> d[i];
		sum += d[i];
		d[i] += d[i-1];
	}
	lint dap = 1e18;
	for(int i=1; i<=n; i++){
		lint ret = 0;
		for(int j=1; j<=n; j++){
			int dis = abs(d[i-1] - d[j-1]);
			ret += 1ll * min(dis, sum - dis) * a[j];
		}
		dap = min(dap, ret);
	}
	cout << dap;
}
