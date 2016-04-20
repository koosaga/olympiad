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
 
vector<pi> lowx, lowy, highx, highy;
vector<int> vx, vy;
 
int n, h, w;
pi a[100005];
 
void input(){
	scanf("%d %d %d",&h,&w,&n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first, &a[i].second);
		vx.push_back(a[i].first);
		vy.push_back(a[i].second);
	}
	sort(vx.begin(), vx.end());
	sort(vy.begin(), vy.end());
	vx.resize(unique(vx.begin(), vx.end()) - vx.begin());
	vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
	sort(a,a+n);
	for(int i=0; i<n;){
		int e = i;
		while(e < n && a[i].first == a[e].first) e++;
		if(a[i].second != 1) lowy.push_back(pi(a[i].first, a[i].second - 1));
		if(a[e-1].second != w) highy.push_back(pi(a[i].first, a[e-1].second + 1));
		i = e;
	}
	for(int i=0; i<n; i++){
		swap(a[i].first, a[i].second);
	}
	sort(a,a+n);
	for(int i=0; i<n;){
		int e = i;
		while(e < n && a[i].first == a[e].first) e++;
		if(a[i].second != 1) lowx.push_back(pi(a[i].first, a[i].second - 1));
		if(a[e-1].second != h) highx.push_back(pi(a[i].first, a[e-1].second + 1));
		i = e;
	}
	for(int i=0; i<n; i++){
		swap(a[i].first, a[i].second);
	}
}
 
int get_between(vector<int> &v, int s, int e){
	return upper_bound(v.begin(), v.end(), e) - lower_bound(v.begin(), v.end(), s);
}
 
set<int> s;
 
int main(){
	input();
	int ret = 0;
	for(auto &i : lowx){
	//	printf("x [1 ~ %d], %d\n",i.second, i.first);
		ret = max(ret, i.second - 1 - get_between(vx, 1, i.second - 1));
	}
	for(auto &i : highx){
	//	printf("x [%d ~ %d], %d\n",i.second, h, i.first);
		ret = max(ret, h - i.second - get_between(vx, i.second + 1, h));
	}
	for(auto &i : lowy){
	//	printf("y [1 ~ %d], %d\n",i.second, i.first);
		ret = max(ret, i.second - 1- get_between(vy, 1, i.second - 1));
	}
	for(auto &i : highy){
	//	printf("y [%d ~ %d], %d\n",i.second, w, i.first);
		ret = max(ret, w - i.second - get_between(vy, i.second + 1, w));
	}
	sort(lowx.begin(), lowx.end(), [&](const pi &a, const pi &b){
		return a.first > b.first;
	});
	sort(lowy.begin(), lowy.end(), [&](const pi &a, const pi &b){
		return a.second > b.second;
	});
	int pt = 0;
	for(auto &i : lowx){
		while(pt < lowy.size() && lowy[pt].second >= i.first){
			s.insert(lowy[pt++].first);
		}
		auto t = s.upper_bound(i.second);
		if(t == s.begin()) continue;
		t--;
		ret = max(ret, i.first - 1 - get_between(vy, 1, i.first - 1)
			+ *t - 1 - get_between(vx, 1, *t - 1));
	}
	s.clear();
	pt = 0;
	sort(lowx.begin(), lowx.end(), [&](const pi &a, const pi &b){
		return a.first < b.first;
	});
	sort(highy.begin(), highy.end(), [&](const pi &a, const pi &b){
		return a.second < b.second;
	});
	for(auto &i : lowx){
		while(pt < highy.size() && highy[pt].second <= i.first){
			s.insert(highy[pt++].first);
		}
		auto t = s.upper_bound(i.second);
		if(t == s.begin()) continue;
		t--;
		ret = max(ret, *t - 1 - get_between(vx, 1, *t-1) + 
			w - i.first - get_between(vy, i.first + 1, w));
	}
	s.clear();
	pt = 0;
	sort(highx.begin(), highx.end(), [&](const pi &a, const pi &b){
		return a.first > b.first;
	});
	sort(lowy.begin(), lowy.end(), [&](const pi &a, const pi &b){
		return a.second > b.second;
	});
	for(auto &i : highx){
		while(pt < lowy.size() && i.first <= lowy[pt].second){
			s.insert(lowy[pt++].first);
		}
		auto t = s.lower_bound(i.second);
		if(t == s.end()) continue;
		ret = max(ret, h - *t - get_between(vx, *t+1, h) +
			i.first - 1 - get_between(vy, 1, i.first - 1));
	}
	s.clear();
	pt = 0;
	sort(highx.begin(), highx.end(), [&](const pi &a, const pi &b){
		return a.first < b.first;
	});
	sort(highy.begin(), highy.end(), [&](const pi &a, const pi &b){
		return a.second < b.second;
	});
	// 4
	for(auto &i : highx){
		while(pt < highy.size() && i.first >= highy[pt].second){
			s.insert(highy[pt++].first);
		}
		auto t = s.lower_bound(i.second);
		if(t == s.end()) continue;
		ret = max(ret, h - *t - get_between(vx, *t + 1, h) + 
			w - i.first - get_between(vy, i.first + 1, w));
	}
	printf("%lld\n",ret + 1ll * (h - vx.size()) * (w - vy.size()));
}