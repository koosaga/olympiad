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
#include <assert.h>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
typedef bitset<505> bs;

set<vector<lint>> s;
int n, a[505];

int main(){
	cin >> n;
	for(int i=0; i<n; i++) cin >> a[i];
	for(int i=0; i<n; i++){
		vector<lint> v(8);
		for(int j=i; j<n; j++){
			v[a[j] >> 6] |= (1ll << (a[j] & 63));
			s.insert(v);
		}
	}
	cout << s.size();
}

