#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <time.h>
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
const int MAXN = 250005;
using pi = pair<int, int>;

int n, k;
pi a[MAXN];
int nxt[MAXN];

lint dist(pi x, pi y){
	int dx = x.first - y.first;
	int dy = x.second - y.second;
	return 1ll * dx * dx + 1ll * dy * dy;
}

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

bool awkward(pi s1, pi e1, pi s2, pi e2){
	return ccw(pi(0, 0), pi(e1.first - s1.first, e1.second - s1.second),
			pi(e2.first - s2.first, e2.second - s2.second)) >= 0;
}

lint cost(int s, int e){
    if(s > e) return 0;
    e = nxt[e];
	vector<pi> v, w;
	for(int i=s; i<=e; i++){
		while(v.size() >= 2 && ccw(v[v.size()-2], v.back(), a[i]) <= 0){
			v.pop_back();
		}
		v.push_back(a[i]);
	}
	for(int i=e; i>=s; i--){
		while(w.size() >= 2 && ccw(w[w.size()-2], w.back(), a[i]) <= 0){
			w.pop_back();
		}
		w.push_back(a[i]);
	}
	for(int i=1; i<w.size()-1; i++) v.push_back(w[i]);
	lint ret = 0;
	int p = 0;
	for(int i=0; i<v.size(); i++){
		while(p+1 < v.size() && awkward(v[i], v[i+1], v[p], v[p+1])){
			ret = max(ret, dist(v[i], v[p]));
			p++;
		}
		ret = max(ret, dist(v[i], v[p]));
	}
	return ret;
}

int trial(lint x){
	int curlst = 0;
	int itr = 0;
	while(curlst < n){
		itr++;
		int thres_st = 0;
		for(int i=0; curlst + (1<<i) <= n; i++){
			if(cost(curlst + 1, curlst + (1<<i)) <= x){
				thres_st = (1<<i);
			}
			else break;
		}
		int thres_ed = min(thres_st * 2, n - curlst);
		while(thres_st != thres_ed){
			int m = (thres_st + thres_ed + 1) / 2;
			if(cost(curlst + 1, curlst + m) <= x){
				thres_st = m;
			}
			else thres_ed = m-1;
		}
		if(thres_st == 0) return 1e9;
		curlst += thres_st;
		curlst = nxt[curlst];
	}
	return itr;
}

int main(){
	scanf("%d %d",&n,&k);
	for(int i=1; i<=n; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
	}
	sort(a+1, a+n+1);
	for(int i=n; i; i--){
	    nxt[i] = i;
	    if(i+1 <= n && a[i].first == a[i+1].first) nxt[i] = nxt[i+1];
	}
	lint s = 0, e = (1ll << 61);
	while(s != e){
		lint m = (s+e)/2;
		if(trial(m) <= k) e = m;
		else s = m + 1;
	}
	cout << s << endl;
}
