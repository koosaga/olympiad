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

int n, a[100005], b[100005];

lint trial(int p){
	lint ret = 0;
	int sa = 0, sb = 0;
	for(int i=0; i<n; i++){
		sa += a[i];
		sb += b[i];
		ret += abs(sa - p - sb);
	}
	return ret;
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> a[i] >> b[i];
	}
	lint ret = 1e18;
	int s = -1e9, e = 1e9;
	while(s != e){
		int m = s + e;
		if(m < 0) m = (m-1) / 2;
		else m = m/2;
		if(trial(m) < trial(m+1)) e = m;
		else s = m+1;
	}
	cout << trial(s);
}