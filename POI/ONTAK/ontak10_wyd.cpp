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
 
int n; lint m;
set<lint> s;
 
int main(){
	cin >> n >> m;
	s.insert(0);
	lint sum = 0, ret = 0;
	for(int i=1; i<=n; i++){
		lint t;
		scanf("%lld",&t);
		sum = (sum + t) % m;
		if(sum < 0) sum += m;
		auto x = s.upper_bound(sum);
		if(x != s.end()){
			ret = max(ret, sum - *x + m);
		}
		else{
			ret = max(ret, sum - *s.begin());
		}
		s.insert(sum);
	}
	cout << ret;
}