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

pi s, camp[10005], tree[2005];
int c, n;
bool ok[10005];

bool ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 > 1ll * dy1 * dx2;
}

void solve(int p){
	vector<pi> ccwl, ccwh;
	for(int i=0; i<n; i++){
		if(p == i) continue;
		if(ccw(s, tree[p], tree[i])){
			ccwl.push_back(tree[i]);
		}
		else{
			ccwh.push_back(tree[i]);
		}
	}
	auto cmp = [&](const pi &a, const pi &b){
		return ccw(tree[p], a, b);
	};
	if(ccwl.empty()){
		pi st = *min_element(ccwh.begin(), ccwh.end(), cmp);
		pi ed = *max_element(ccwh.begin(), ccwh.end(), cmp);
		for(int i=0; i<c; i++){
			if(ccw(st, tree[p], camp[i]) && !ccw(ed, tree[p], camp[i])){
				ok[i] = 0;
			}
		}
		return;
	}
	else if(ccwh.empty()){
		pi st = *min_element(ccwl.begin(), ccwl.end(), cmp);
		pi ed = *max_element(ccwl.begin(), ccwl.end(), cmp);
		for(int i=0; i<c; i++){
			if(ccw(st, tree[p], camp[i]) && !ccw(ed, tree[p], camp[i])){
				ok[i] = 0;
			}
		}
		return;
	}
	pi t = *min_element(ccwl.begin(), ccwl.end(), cmp);
	for(int i=0; i<c; i++){
		if(!ccw(s, tree[p], camp[i]) && ccw(t, tree[p], camp[i])){
			ok[i] = 0;
		}
	}
	t = *max_element(ccwh.begin(), ccwh.end(), cmp);
	for(int i=0; i<c; i++){
		if(ccw(s, tree[p], camp[i]) && !ccw(t, tree[p], camp[i])){
			ok[i] = 0;
		}
	}
}

int main(){
	cin >> c >> n >> s.first >> s.second;
	cin >> c;
	for(int i=0; i<c; i++){
		cin >> camp[i].first >> camp[i].second;
	}
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> tree[i].first >> tree[i].second;
	}
	fill(ok, ok + c, true);
	for(int i=0; i<n; i++){
		solve(i);
	}
	printf("%d\n",count(ok, ok + c, true));
	for(int i=0; i<c; i++){
		if(ok[i]) printf("%d ",i+1);
	}
}