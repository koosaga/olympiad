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
int x[2005], y[2005], m[2005];
vector<int> ls;

lint solve(int s, int e){
	int sl = 1e9, el = -1e9;
	vector<pi> v;
	for(int i=0; i<n; i++){
		if(max(x[i], s) < min(x[i] + m[i], e)){
			sl = min(sl, y[i]);
			el = max(el, y[i] + x[i] + m[i] - s);
			v.push_back(pi(y[i], 1));
			v.push_back(pi(y[i] + x[i] + m[i] - e, -1));
		}
	}
	sort(v.begin(), v.end());
	int pok = e - s, cur = 0;
	lint ret = 2ll * (el - sl) * pok - 1ll * pok * pok;
	for(int i=0; i<v.size(); ){
		int e = i;
		while(e < v.size() && v[e].first == v[i].first){
			cur += v[e].second;
			e++;
		}
		if(e < v.size() && cur == 0){
			int curl = v[e].first - v[i].first;
			ret -= 1ll * curl * curl - 1ll * max(curl - pok, 0) * max(curl - pok, 0);
		}
		i = e;
	}
	return ret;
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> x[i] >> y[i] >> m[i];
		ls.push_back(x[i]);
		ls.push_back(x[i]+m[i]);
	}
	sort(ls.begin(), ls.end());
	ls.resize(unique(ls.begin(), ls.end()) - ls.begin());
	lint ret = 0;
	for(int i=0; i<ls.size()-1; i++){
		ret += solve(ls[i], ls[i+1]);
	}
	if(ret % 2 == 1) printf("%lld.5",ret/2);
	else printf("%lld.0",ret/2);
}