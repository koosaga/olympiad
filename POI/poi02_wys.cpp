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
typedef pair<lint, int> pi;

int n, a[100005];

int main(){
	cin >> n;
	int sum = 0;
	for(int i=0; i<n; i++) cin >> a[i], sum += a[i];
	for(int i=0; i<n; i++) a[i+n] = a[i];
	if(*max_element(a, a+n) * 2 >= sum){
		printf("%d\n", sum - *max_element(a, a+n));
		return 0;
	}
	int cur = 0, e = 0, ret = 0;
	for(int i=0; i<n; i++){
		while(cur + a[e] <= sum / 2) cur += a[e++];
		ret = max(ret, cur);
		cur -= a[i];
	}
	cout << ret;
}
