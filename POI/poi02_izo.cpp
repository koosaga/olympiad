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

int n, a[100005];

int main(){
	cin >> n;
	int ret = 0;
	for(int i=0; i<n; i++) cin >> a[i], ret += a[i];
	sort(a, a+n);
	for(int i=0; i<n-1-i; i++) ret += a[n-1-i] - a[i];
	cout << ret;
}
